1. Run "pip install pandas numpy" if they have not already been installed.

2. Run "python q2main.py <dataset_dir>", where <dataset_dir> is the path of the directory where the dataset is residing on your computer. For example, in my case, it was '/content/gdrive/MyDrive/dataset'. load_dataset() function has a default parameter as this system argument that you are going to assign, so you do not need to do anything further.

3. 3 different models (unsmoothed multinomial, smoothed multinomial, smoothed Bernoulli, respectively) accuracy results and confusion matrices are directly printed in the main() in a very clear format.