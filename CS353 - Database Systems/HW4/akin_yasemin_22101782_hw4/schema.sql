CREATE TABLE customer (
    cid CHAR(5) NOT NULL,
    name VARCHAR(30) NOT NULL,
    bdate DATE NOT NULL,
    city VARCHAR(20) NOT NULL,
    nationality VARCHAR(20) NOT NULL,
    PRIMARY KEY (cid)
);

CREATE TABLE account (
    aid CHAR(8) NOT NULL,
    branch VARCHAR(20) NOT NULL,
    balance FLOAT NOT NULL,
    openDate DATE NOT NULL,
    city VARCHAR(20) NOT NULL,
    PRIMARY KEY (aid)
);

CREATE TABLE owns (
    cid CHAR(5) NOT NULL,
    aid CHAR(8) NOT NULL,
    PRIMARY KEY (cid, aid),
    FOREIGN KEY (cid) REFERENCES customer(cid),
    FOREIGN KEY (aid) REFERENCES account(aid)
);

INSERT INTO customer (cid, name, bdate, city, nationality) VALUES
('10001', 'Ayse', '08/09/1990', 'Ankara', 'TC'),
('10002', 'Ali', '16/10/1985', 'Ankara', 'TC'),
('10003', 'Ahmet', '15/02/1997', 'Izmir', 'TC'),
('10004', 'John', '26/04/2003', 'Istanbul', 'UK');

INSERT INTO account (aid, branch, balance, openDate, city) VALUES
('A0000001', 'Kizilay', 40000.00, '01/11/2019', 'Ankara'),
('A0000002', 'Kadikoy', 228000.00, '05/01/2011', 'Istanbul'),
('A0000003', 'Cankaya', 432000.00, '14/05/2016', 'Ankara'),
('A0000004', 'Bilkent', 100500.00, '01/06/2023', 'Ankara'),
('A0000005', 'Tandogan', 77800.00, '20/03/2013', 'Ankara'),
('A0000006', 'Konak', 25000.00, '22/01/2022', 'Izmir'),
('A0000007', 'Bakirkoy', 6000.00, '21/04/2017', 'Istanbul');

INSERT INTO owns (cid, aid) VALUES
('10001', 'A0000001'),
('10001', 'A0000002'),
('10001', 'A0000003'),
('10001', 'A0000004'),
('10002', 'A0000001'),
('10002', 'A0000003'),
('10002', 'A0000005'),
('10003', 'A0000006'),
('10003', 'A0000007'),
('10004', 'A0000006');