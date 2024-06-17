#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <assert.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <errno.h>
#include <linux/msdos_fs.h>
#include <ctype.h>

#define FALSE 0
#define TRUE 1

#define ATTR_VOLUME_ID   0x08
#define ATTR_DIRECTORY   0x10

#define SECTORSIZE 512   // bytes
#define CLUSTERSIZE  1024  // bytes

#define FAT_START_SECTOR  32

#define N_ROOTDIR_CLUSTERS  1   //at most 30 files + 2 (one for root directory one for FILE1.BIN entries) = 32 entries
//#define SECTORS_PER_CLUSTER  2
#define ROOTDIR_CLUSTER  2
#define DIRECTORYENTRY_PER_CLUSTER 32

int readsector (int fd, unsigned char *buf, unsigned int snum);
int writesector (int fd, unsigned char *buf, unsigned int snum);
void print_data(unsigned char *buf, size_t size);
void print_sector(unsigned char *buf);
void print_cluster(unsigned char *buf);
int readcluster(int fd, unsigned char *buf, unsigned int cnum);
int writecluster(int fd, unsigned char *buf, unsigned int cnum);
void list_directory_contents(int fd);
int get_next_cluster(int fd, unsigned int current_cluster);
void read_file_ascii(int fd, const char* filename);
void read_file_binary(int fd, const char* filename);
void format_filename(const char *input, char *formatted_name);
void create_file(int fd, const char* filename);
void display_help();
void delete_file(int fd, const char* filename);
int set_fat_entry(int fd, unsigned int cluster, unsigned int value);
unsigned int allocate_new_cluster(int fd, unsigned int prev_cluster);
void write_file(int fd, const char* input_filename, unsigned int offset, unsigned int n, unsigned char data);

// command parse logic
int main(int argc, char *argv[]) {
    if (argc < 2 || (argc == 2 && strcmp(argv[1], "-h") == 0)) {
        display_help();
        return 0;
    }

    if (argc < 3) {
        printf("Error: Too few arguments.\n");
        display_help();
        return EXIT_FAILURE;
    }

    const char *diskImage = argv[1];
    const char *operation = argv[2];

    int fd = open(diskImage, O_SYNC | O_RDWR);
    if (fd < 0) {
        perror("Failed to open disk image");
        return EXIT_FAILURE;
    }

    if (strcmp(operation, "-l") == 0) {
        list_directory_contents(fd);
    } else if (strcmp(operation, "-r") == 0) {
        if (argc < 5) {
            printf("Error: Missing filename for read operation.\n");
            close(fd);
            return EXIT_FAILURE;
        }
        if (strcmp(argv[3], "-a") == 0) {
            read_file_ascii(fd, argv[4]);
        } else if (strcmp(argv[3], "-b") == 0) {
            read_file_binary(fd, argv[4]);
        } else {
            printf("Error: Invalid read option. Use -a or -b.\n");
        }
    } else if (strcmp(operation, "-c") == 0) {
        if (argc < 4) {
            printf("Error: Missing filename for create operation.\n");
            close(fd);
            return EXIT_FAILURE;
        }
        create_file(fd, argv[3]);
    } else if (strcmp(operation, "-d") == 0) {
        if (argc < 4) {
            printf("Error: Missing filename for delete operation.\n");
            close(fd);
            return EXIT_FAILURE;
        }
        delete_file(fd, argv[3]);
    } else if (strcmp(operation, "-w") == 0) {
        if (argc < 7) {
            printf("Error: Missing arguments for write operation.\n");
            close(fd);
            return EXIT_FAILURE;
        }
        int offset = atoi(argv[4]);
        int n = atoi(argv[5]);
        unsigned char data = (unsigned char)atoi(argv[6]);
        write_file(fd, argv[3], offset, n, data);
    } else {
        printf("Invalid command: %s\n", operation);
        display_help();
    }

    close(fd);
    return 0;
}

int 
readsector (int fd, unsigned char *buf,unsigned int snum)
{
	off_t offset;
	int n;
	offset = snum * SECTORSIZE;
	lseek (fd, offset, SEEK_SET);
	n  = read (fd, buf, SECTORSIZE);
	if (n == SECTORSIZE)
	    return (0);
	else
        return (-1);
}

int 
writesector (int fd, unsigned char *buf, unsigned int snum)
{
	off_t offset;
	int n;
	offset = snum * SECTORSIZE;
	lseek (fd, offset, SEEK_SET);
	n  = write (fd, buf, SECTORSIZE);
        fsync (fd);
        if (n == SECTORSIZE)
	     return (0);
	else
             return (-1);
}

void print_data(unsigned char *buf, size_t size) {
    printf("Data output:\n");
    for (int i = 0; i < size; i++) {
        if (i % 16 == 0) printf("\n%08x: ", i);  
        printf("%02x ", buf[i]);                

        if (i % 16 == 15) {
            printf("\n");
        }
    }
    printf("\n");
}

void print_sector(unsigned char *buf) {
    print_data(buf, SECTORSIZE);
}

void print_cluster(unsigned char *buf) {
    print_data(buf, CLUSTERSIZE);
}

int readcluster(int fd, unsigned char *buf, unsigned int cnum) {

    unsigned char sector[SECTORSIZE];
    if (readsector(fd, sector, 0) != 0) {
        printf("Failed to read boot sector\n");
        return -1;
    }

    struct fat_boot_sector *bp = (struct fat_boot_sector *) sector;

    unsigned int firstDataSector = bp->reserved + (bp->fats * bp->fat32.length);
    unsigned int firstSectorOfCluster = firstDataSector + (cnum - 2) * bp->sec_per_clus;

    unsigned int totalBytes = bp->sec_per_clus * SECTORSIZE;
    unsigned int offset = firstSectorOfCluster * SECTORSIZE;

    lseek(fd, offset, SEEK_SET);
    int bytesRead = read(fd, buf, totalBytes);
    if (bytesRead == totalBytes) {
        return 0; 
    } else {
        perror("Failed to read cluster");
        return -1; 
    }
}

int writecluster(int fd, unsigned char *buf, unsigned int cnum) {
    unsigned char sector[SECTORSIZE];
    int sectors_per_cluster;

    if (readsector(fd, sector, 0) != 0) {
        perror("Failed to read boot sector");
        return -1;
    }

    struct fat_boot_sector *bp = (struct fat_boot_sector *) sector;

    sectors_per_cluster = bp->sec_per_clus;

    unsigned int firstSectorOfCluster = bp->reserved + (bp->fats * bp->fat32.length) + ((cnum - 2) * sectors_per_cluster);

    off_t offset = (off_t)firstSectorOfCluster * SECTORSIZE;

    for (int i = 0; i < sectors_per_cluster; i++) {
        lseek(fd, offset + (i * SECTORSIZE), SEEK_SET);
        if (write(fd, buf + (i * SECTORSIZE), SECTORSIZE) != SECTORSIZE) {
            perror("Failed to write sector");
            return -1;
        }
        fsync(fd);  
    }

    return 0;
}

void list_directory_contents(int fd) {
    struct msdos_dir_entry* dep;
    char filename[13]; // Buffer to hold the filename.extension\0 (8+3+2)
    unsigned char cluster[CLUSTERSIZE];

    if (readcluster(fd, cluster, ROOTDIR_CLUSTER) != 0) {
        printf("Failed to read cluster 2\n");
        return;
    }

    dep = (struct msdos_dir_entry *) cluster;

    for (int i = 0; i < CLUSTERSIZE / DIRECTORYENTRY_PER_CLUSTER; i++) {
        if (dep[i].name[0] == 0x00) {
            // No more entries
            break;
        }
        if (dep[i].name[0] == 0xE5) {
            // This entry is marked as deleted
            continue;
        }

        // Filter out the volume label and subdirectory attributes
        if ((dep[i].attr & ATTR_VOLUME_ID) || (dep[i].attr & ATTR_DIRECTORY)) {
            continue;
        }

        // Extract filename and extension
        char fname[9], ext[4]; // Size includes space for null terminator
        strncpy(fname, (char*)dep[i].name, 8);
        fname[8] = '\0';  // Ensure null termination
        strncpy(ext, (char*)(dep[i].name + 8), 3);
        ext[3] = '\0';    // Ensure null termination

        // Right-trim spaces from the filename and extension
        int j = 7; 
        while (j >= 0 && fname[j] == ' ') fname[j--] = '\0';
        int k = 2; 
        while (k >= 0 && ext[k] == ' ') ext[k--] = '\0';

        if (strlen(ext) > 0)
            sprintf(filename, "%s.%s", fname, ext);
        else
            strcpy(filename, fname);

        printf("%-12s %d\n", filename, dep[i].size);
    }
}

int get_next_cluster(int fd, unsigned int current_cluster) {
    unsigned int fat_offset = current_cluster * 4; 
    unsigned int fat_sector = FAT_START_SECTOR + (fat_offset / SECTORSIZE);
    unsigned int ent_offset = fat_offset % SECTORSIZE;

    unsigned char buf[SECTORSIZE];
    if (readsector(fd, buf, fat_sector) != 0) {
        perror("Failed to read FAT sector");
        return -1;  
    }

    unsigned int next_cluster = *(unsigned int *)(buf + ent_offset) & 0x0FFFFFFF;  
    if (next_cluster >= 0x0FFFFFF8) return -1; 
    return next_cluster;
}

void read_file_ascii(int fd, const char* input_filename) {
    unsigned char buf[CLUSTERSIZE];
    char formatted_filename[MSDOS_NAME];  
    format_filename(input_filename, formatted_filename); 

    if (readcluster(fd, buf, ROOTDIR_CLUSTER) != 0) {
        printf("Failed to read the root directory cluster\n");
        return;
    }

    struct msdos_dir_entry *dep = (struct msdos_dir_entry *) buf;
    int found = 0;
    struct msdos_dir_entry de;

    for (int i = 0; i < DIRECTORYENTRY_PER_CLUSTER; i++) {
        if (strncmp((char *)dep[i].name, formatted_filename, MSDOS_NAME) == 0 && dep[i].name[0] != 0xE5) {
            de = dep[i];
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("File not found: %s\n", input_filename);
        return;
    }

    unsigned int cluster = ((unsigned int)de.starthi << 16) | de.start;
    while (cluster >= 0x00000002 && cluster < 0x0FFFFFF8) {
        if (cluster == 0x0FFFFFF7) {
            printf("Error: Bad cluster detected at cluster %u\n", cluster);
            break;
        }

        if (readcluster(fd, buf, cluster) != 0) {
            printf("Error reading cluster %u\n", cluster);
            break;
        }

        for (int i = 0; i < CLUSTERSIZE; i++) {
            if (isprint(buf[i]) || isspace(buf[i])) {
                putchar(buf[i]);
            }
        }

        int next_cluster = get_next_cluster(fd, cluster);
        if (next_cluster < 0) {
            break;
        }
        cluster = next_cluster;
    }
}

void read_file_binary(int fd, const char* input_filename) {
    unsigned char buf[CLUSTERSIZE];
    char formatted_filename[MSDOS_NAME];  
    format_filename(input_filename, formatted_filename); 

    if (readcluster(fd, buf, ROOTDIR_CLUSTER) != 0) {
        printf("Failed to read the root directory cluster\n");
        return;
    }

    struct msdos_dir_entry *dep = (struct msdos_dir_entry *) buf;
    int entries_per_cluster = CLUSTERSIZE / sizeof(struct msdos_dir_entry);
    int found = 0;
    struct msdos_dir_entry de;

    for (int i = 0; i < entries_per_cluster; i++) {
        if (strncmp((char *)dep[i].name, formatted_filename, MSDOS_NAME) == 0 && dep[i].name[0] != 0xE5) {
            de = dep[i];
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("File not found: %s\n", input_filename);
        return;
    }

    unsigned int cluster = ((unsigned int)de.starthi << 16) | de.start;
    unsigned int totalOffset = 0;
    unsigned int fileSize = de.size;

    while (cluster >= 0x00000002 && cluster < 0x0FFFFFF8 && totalOffset < fileSize) {
        if (readcluster(fd, buf, cluster) != 0) {
            printf("Error reading cluster %u\n", cluster);
            break;
        }

        int bytesToPrint = CLUSTERSIZE;
        if (totalOffset + CLUSTERSIZE > fileSize) {
            bytesToPrint = fileSize - totalOffset;  
        }

        for (int i = 0; i < bytesToPrint; i++) {
            if ((totalOffset + i) % 16 == 0) printf("\n%08x: ", totalOffset + i);
            printf("%02x ", buf[i]);

            if ((totalOffset + i) % 16 == 15) {
                printf("\n");
            }
        }
        totalOffset += bytesToPrint;
        if (totalOffset >= fileSize) break;  

        int next_cluster = get_next_cluster(fd, cluster);
        if (next_cluster < 0) {
            break;
        }
        cluster = next_cluster;
    }
}

void format_filename(const char *input, char *formatted_name) {
    int name_length = 0;
    int ext_length = 0;
    const char *ext = strrchr(input, '.'); 

    if (ext != NULL) {
        name_length = ext - input;
        ext_length = strlen(ext + 1);
    } else {
        name_length = strlen(input);
    }

    for (int i = 0; i < 8; i++) {
        if (i < name_length) {
            formatted_name[i] = toupper(input[i]);
        } else {
            formatted_name[i] = ' ';
        }
    }

    for (int i = 0; i < 3; i++) {
        if (ext != NULL && i < ext_length) {
            formatted_name[8 + i] = toupper(ext[i + 1]);
        } else {
            formatted_name[8 + i] = ' ';
        }
    }
}

void create_file(int fd, const char *filename) {
    unsigned char cluster[CLUSTERSIZE];
    struct msdos_dir_entry *dep;

    const char *dot = strrchr(filename, '.');
    int name_length = (dot) ? dot - filename : strlen(filename);
    int ext_length = (dot) ? strlen(dot + 1) : 0;

    if (name_length > 8 || ext_length > 3) {
        printf("Error: Filename must be in 8.3 format.\n");
        return;
    }

    if (readcluster(fd, cluster, ROOTDIR_CLUSTER) != 0) {
        perror("Failed to read root directory cluster");
        return;
    }

    dep = (struct msdos_dir_entry *)cluster;
    int found_empty = 0;
    int i;

    char formatted_name[MSDOS_NAME];
    format_filename(filename, formatted_name); 

    for (i = 0; i < DIRECTORYENTRY_PER_CLUSTER; i++) {
        if (strncmp((char *)dep[i].name, formatted_name, MSDOS_NAME) == 0 && dep[i].name[0] != 0xE5) {
            printf("A file with the name '%s' already exists\n", filename);
            return;
        }
    }

    for (i = 0; i < DIRECTORYENTRY_PER_CLUSTER; i++) {
        if (dep[i].name[0] == 0x00 || dep[i].name[0] == 0xE5) {
            found_empty = 1;
            break;
        }
    }

    if (!found_empty) {
        printf("No empty entries in root directory\n");
        return;
    }

    memcpy(dep[i].name, formatted_name, MSDOS_NAME); 
    dep[i].attr = 0x20; 
    dep[i].size = 0;   
    dep[i].start = 0;  
    dep[i].starthi = 0; 
    dep[i].ctime = dep[i].cdate = dep[i].adate = 0; 
    if (writecluster(fd, cluster, ROOTDIR_CLUSTER) != 0) {
        perror("Failed to write root directory cluster");
        return;
    }

    printf("File created successfully\n");
}

void delete_file(int fd, const char *input_filename) {
    unsigned char cluster[CLUSTERSIZE];
    char formatted_filename[MSDOS_NAME];  
    format_filename(input_filename, formatted_filename); 

    struct msdos_dir_entry *dep;

    if (readcluster(fd, cluster, ROOTDIR_CLUSTER) != 0) {
        perror("Failed to read root directory cluster");
        return;
    }

    dep = (struct msdos_dir_entry *)cluster;
    int found = 0;
    int i;

    for (i = 0; i < DIRECTORYENTRY_PER_CLUSTER; i++) {
        if (strncmp((char *)dep[i].name, formatted_filename, MSDOS_NAME) == 0 && dep[i].name[0] != 0xE5) {
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("File '%s' not found\n", input_filename);
        return;
    }

    dep[i].name[0] = 0xE5;

    if (writecluster(fd, cluster, ROOTDIR_CLUSTER) != 0) {
        perror("Failed to write root directory cluster");
        return;
    }

    unsigned int cluster_number = dep[i].start | (dep[i].starthi << 16);
    while (cluster_number >= 0x00000002 && cluster_number < 0x0FFFFFF8) {
        unsigned int next_cluster = get_next_cluster(fd, cluster_number);
        set_fat_entry(fd, cluster_number, 0x00000000); 

        if (next_cluster >= 0x0FFFFFF8) { 
            break;
        }
        cluster_number = next_cluster;
    }

    printf("File '%s' deleted successfully\n", input_filename);
}

int set_fat_entry(int fd, unsigned int cluster, unsigned int value) {
    unsigned char sector[SECTORSIZE];
    unsigned int fat_offset, fat_sector, ent_offset;

    fat_offset = cluster * 4;  
    fat_sector = FAT_START_SECTOR + (fat_offset / SECTORSIZE);
    ent_offset = fat_offset % SECTORSIZE;

    if (readsector(fd, sector, fat_sector) != 0) {
        perror("Failed to read FAT sector");
        return -1;
    }

    unsigned int *entry = (unsigned int *)(sector + ent_offset);
    *entry = (*entry & 0xF0000000) | (value & 0x0FFFFFFF);  

    if (writesector(fd, sector, fat_sector) != 0) {
        perror("Failed to write FAT sector");
        return -1;
    }

    return 0;
}

void display_help(void) {
    printf("\nUsage and available operations:\n");
    printf("  ./fatmod -h                      Display help information. This option does not require <imagefile>.\n");
    printf("  ./fatmod <imagefile> -l                      List directory contents of the disk image.\n");
    printf("  ./fatmod <imagefile> -r -a <filename>        Read and display the file named <filename> in ASCII form from the disk image.\n");
    printf("  ./fatmod <imagefile> -r -b <filename>        Read and display the file named <filename> in binary form from the disk image.\n");
    printf("  ./fatmod <imagefile> -c <filename>           Create a new file named <filename> in the root directory of the disk image.\n");
    printf("  ./fatmod <imagefile> -d <filename>           Delete the file named <filename> from the disk image and free up associated space.\n");
    printf("  ./fatmod <imagefile> -w <filename> <offset> <n> <data>  Write 'data' to the file named <filename> starting at 'offset' and repeat 'data' for 'n' times.\n");
    printf("\n");
}

void write_file(int fd, const char* input_filename, unsigned int offset, unsigned int n, unsigned char data) {
    unsigned char cluster[CLUSTERSIZE];
    char formatted_filename[MSDOS_NAME];
    format_filename(input_filename, formatted_filename);

    struct msdos_dir_entry *dep;

    if (readcluster(fd, cluster, ROOTDIR_CLUSTER) != 0) {
        perror("Failed to read root directory cluster");
        return;
    }

    dep = (struct msdos_dir_entry *)cluster;
    unsigned int found_index = -1;
    unsigned int file_size = 0, start_cluster = 0;

    for (int i = 0; i < DIRECTORYENTRY_PER_CLUSTER; i++) {
        if (strncmp((char *)dep[i].name, formatted_filename, MSDOS_NAME) == 0 && dep[i].name[0] != 0xE5) {
            found_index = i;
            file_size = dep[i].size;
            start_cluster = dep[i].start | (dep[i].starthi << 16);
            break;
        }
    }

    if (found_index == -1) {
        printf("File '%s' not found.\n", input_filename);
        return;
    }

    if (offset > file_size) {
        printf("Error: OFFSET %d is beyond the current file size %u.\n", offset, file_size);
        return;
    }

    unsigned int cluster_num = start_cluster;
    int cluster_offset = offset;
    while (cluster_offset >= CLUSTERSIZE) {
        unsigned int next_cluster = get_next_cluster(fd, cluster_num);
        if (next_cluster >= 0x0FFFFFF8) {
            next_cluster = allocate_new_cluster(fd, cluster_num);
            if (next_cluster == (unsigned int)-1) {
                perror("Failed to allocate new cluster");
                return;
            }
        }
        cluster_num = next_cluster;
        cluster_offset -= CLUSTERSIZE;
    }

    if (readcluster(fd, cluster, cluster_num) != 0) {
        perror("Failed to read cluster");
        return;
    }

    int bytes_to_write = n;
    while (bytes_to_write > 0) {
        int write_count = CLUSTERSIZE - cluster_offset;
        write_count = (bytes_to_write < write_count) ? bytes_to_write : write_count;
        memset(cluster + cluster_offset, data, write_count);
        bytes_to_write -= write_count;
        cluster_offset += write_count;
        if (cluster_offset >= CLUSTERSIZE) {
            if (writecluster(fd, cluster, cluster_num) != 0) {
                perror("Failed to write cluster");
                return;
            }
            unsigned int next_cluster = get_next_cluster(fd, cluster_num);
            if (next_cluster >= 0x0FFFFFF8) {
                next_cluster = allocate_new_cluster(fd, cluster_num);
                if (next_cluster == (unsigned int)-1) {
                    perror("Failed to allocate new cluster");
                    return;
                }
            }
            cluster_num = next_cluster;
            cluster_offset = 0;
            if (readcluster(fd, cluster, cluster_num) != 0) {
                perror("Failed to read new cluster");
                return;
            }
        }
    }
    
    if (writecluster(fd, cluster, cluster_num) != 0) {
        perror("Failed to write final cluster");
        return;
    }

    unsigned int new_size = offset + n;
   
    if (readcluster(fd, cluster, ROOTDIR_CLUSTER) != 0) {
        perror("Failed to read root directory cluster");
        return;
    }
    if (new_size > file_size) {
        dep[found_index].size = new_size;  
        if (writecluster(fd, cluster, ROOTDIR_CLUSTER) != 0) {  
            perror("Failed to update directory entry");
        } else {
            printf("File size updated successfully. New size is %u bytes.\n", dep[found_index].size);
        }
    } else {
        printf("Data written successfully. No need to update file size.\n");
    }
}

unsigned int allocate_new_cluster(int fd, unsigned int prev_cluster) {
    printf("Allocating new cluster...\n");
    unsigned char *fat_table;
    unsigned int total_clusters, sectors_per_fat;

    unsigned char sector[SECTORSIZE];
    if (readsector(fd, sector, 0) != 0) {
        perror("Failed to read boot sector");
        return (unsigned int)-1; 
    }
    
    struct fat_boot_sector *bp = (struct fat_boot_sector *)sector;
    sectors_per_fat = bp->fat32.length; 
    total_clusters = (sectors_per_fat * SECTORSIZE) / 4;  

    fat_table = (unsigned char *)malloc(sectors_per_fat * SECTORSIZE);
    if (!fat_table) {
        perror("Failed to allocate memory for FAT table");
        return (unsigned int)-1;
    }

    for (unsigned int i = 0; i < sectors_per_fat; i++) {
        if (readsector(fd, fat_table + (i * SECTORSIZE), FAT_START_SECTOR + i) != 0) {
            perror("Failed to read FAT sector");
            free(fat_table);
            return (unsigned int)-1;
        }
    }

    for (unsigned int i = 0; i < total_clusters; i++) {
        unsigned int *entry = (unsigned int *)(fat_table + (i * 4));
        if ((*entry & 0x0FFFFFFF) == 0) {  
            unsigned int new_cluster = i + 2;  
            *entry = 0x0FFFFFF8;  

            if (writesector(fd, fat_table + ((i / (SECTORSIZE / 4)) * SECTORSIZE), FAT_START_SECTOR + (i / (SECTORSIZE / 4))) != 0) {
                perror("Failed to write updated FAT sector");
                free(fat_table);
                return (unsigned int)-1;
            }

            if (prev_cluster != 0) {
                unsigned int *prev_entry = (unsigned int *)(fat_table + ((prev_cluster - 2) * 4));
                *prev_entry = new_cluster;
                if (writesector(fd, fat_table + (((prev_cluster - 2) / (SECTORSIZE / 4)) * SECTORSIZE), FAT_START_SECTOR + ((prev_cluster - 2) / (SECTORSIZE / 4))) != 0) {
                    perror("Failed to update FAT entry for previous cluster");
                    free(fat_table);
                    return (unsigned int)-1;
                }
            }

            free(fat_table);
            return new_cluster;
        }
    }

    printf("No free clusters available.\n");
    free(fat_table);
    return (unsigned int)-1; 
}