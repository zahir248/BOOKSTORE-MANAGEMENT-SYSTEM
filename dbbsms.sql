-- phpMyAdmin SQL Dump
-- version 5.2.0
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1
-- Generation Time: Jan 30, 2023 at 02:40 AM
-- Server version: 10.4.25-MariaDB
-- PHP Version: 8.1.10

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `dbbsms`
--

-- --------------------------------------------------------

--
-- Table structure for table `book`
--

CREATE TABLE `book` (
  `BookID` int(11) NOT NULL,
  `BookName` varchar(100) COLLATE utf8mb4_bin NOT NULL,
  `BookAuthorName` varchar(100) COLLATE utf8mb4_bin NOT NULL,
  `BookPublicationName` varchar(100) COLLATE utf8mb4_bin NOT NULL,
  `BookType` varchar(100) COLLATE utf8mb4_bin NOT NULL,
  `BookPrice` decimal(13,2) NOT NULL,
  `BookQuantity` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_bin;

--
-- Dumping data for table `book`
--

INSERT INTO `book` (`BookID`, `BookName`, `BookAuthorName`, `BookPublicationName`, `BookType`, `BookPrice`, `BookQuantity`) VALUES
(1, 'statistik', 'fauziah', 'utem', 'tutorial', '24.00', 39),
(2, 'database', 'amir', 'utem', 'lab', '36.20', 31),
(3, 'algorithm', 'intan', 'utem', 'tutorial', '19.99', 33),
(4, 'programming', 'sanusi', 'utem', 'lab', '30.99', 38),
(13, 'operating', 'wahidah', 'utem', 'lab', '42.00', 28),
(19, 'workshop', 'ali', 'utem', 'tutorial', '10.00', 22);

-- --------------------------------------------------------

--
-- Table structure for table `bookseller`
--

CREATE TABLE `bookseller` (
  `BooksellerID` int(11) NOT NULL,
  `BooksellerUsername` varchar(100) COLLATE utf8mb4_bin NOT NULL,
  `BooksellerPassword` varchar(100) COLLATE utf8mb4_bin NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_bin;

--
-- Dumping data for table `bookseller`
--

INSERT INTO `bookseller` (`BooksellerID`, `BooksellerUsername`, `BooksellerPassword`) VALUES
(1, 'admin', 'admin'),
(2, '123', '123');

-- --------------------------------------------------------

--
-- Table structure for table `customer`
--

CREATE TABLE `customer` (
  `CustomerID` int(11) NOT NULL,
  `CustomerUsername` varchar(100) COLLATE utf8mb4_bin NOT NULL,
  `CustomerPassword` varchar(100) COLLATE utf8mb4_bin NOT NULL,
  `CustomerPhoneNumber` int(11) NOT NULL,
  `CustomerAddress` varchar(100) COLLATE utf8mb4_bin NOT NULL,
  `CustomerEmail` varchar(100) COLLATE utf8mb4_bin NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_bin;

--
-- Dumping data for table `customer`
--

INSERT INTO `customer` (`CustomerID`, `CustomerUsername`, `CustomerPassword`, `CustomerPhoneNumber`, `CustomerAddress`, `CustomerEmail`) VALUES
(368, 'zahir248', 'zahir248', 149947806, 'melaka', 'zahir248@gmail.com'),
(369, 'eli369', 'eli369', 133562538, 'johor', 'eli@gmail.com'),
(370, 'za', 'za', 149947806, 'za', 'za@gmsil.com'),
(371, 'za', 'za', 149947806, 'za', 'za@gmal.com'),
(372, 'zahir', 'zahir100', 149947806, 'melaka', 'zahir248@gmail.com');

-- --------------------------------------------------------

--
-- Table structure for table `purchase`
--

CREATE TABLE `purchase` (
  `PurchaseID` int(11) NOT NULL,
  `PurchaseQuantity` int(11) NOT NULL,
  `PurchaseDate` date NOT NULL,
  `PurchaseTotalPrice` decimal(13,2) NOT NULL,
  `BookID` int(11) NOT NULL,
  `CustomerID` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_bin;

--
-- Dumping data for table `purchase`
--

INSERT INTO `purchase` (`PurchaseID`, `PurchaseQuantity`, `PurchaseDate`, `PurchaseTotalPrice`, `BookID`, `CustomerID`) VALUES
(372, 2, '2023-01-04', '84.00', 13, 368),
(373, 2, '2023-01-04', '39.98', 3, 368),
(374, 2, '2023-01-04', '48.00', 1, 368),
(375, 3, '2023-01-04', '72.00', 1, 369),
(376, 3, '2023-01-04', '108.60', 2, 369),
(377, 5, '2023-01-04', '154.95', 4, 368),
(378, 2, '2023-01-04', '61.98', 4, 368),
(379, 3, '2023-08-04', '92.97', 4, 369),
(380, 2, '2023-01-04', '66.00', 19, 368),
(381, 3, '2023-01-04', '126.00', 13, 368),
(382, 2, '2023-01-05', '48.00', 1, 369),
(383, 2, '2023-01-05', '72.40', 2, 368),
(384, 1, '2023-01-05', '19.99', 3, 368),
(385, 4, '2023-01-05', '132.00', 19, 369),
(386, 5, '2023-01-05', '99.95', 3, 369),
(387, 1, '2023-01-05', '19.99', 3, 369),
(388, 2, '2023-01-06', '44.00', 19, 368),
(389, 2, '2023-01-06', '44.00', 19, 368),
(390, 10, '2023-01-11', '420.00', 13, 368),
(391, 5, '2023-01-11', '181.00', 2, 368),
(392, 1, '2023-01-12', '22.00', 19, 368),
(393, 2, '2023-01-12', '39.98', 3, 368),
(394, 2, '2023-01-12', '48.00', 1, 369),
(395, 1, '2023-01-12', '36.20', 2, 369),
(396, 1, '2023-01-12', '30.99', 4, 369),
(397, 1, '2023-01-12', '30.99', 4, 369),
(398, 2, '2023-01-12', '84.00', 13, 369),
(399, 3, '2023-01-12', '108.60', 2, 368),
(400, 2, '2023-01-12', '44.00', 19, 368),
(401, 3, '2023-01-12', '66.00', 19, 368),
(402, 2, '2023-01-12', '44.00', 19, 368),
(403, 2, '2023-01-14', '44.00', 19, 368),
(404, 2, '2023-01-16', '48.00', 1, 368),
(405, 5, '2023-01-16', '50.00', 19, 372),
(406, 2, '2023-01-19', '20.00', 19, 368),
(407, 2, '2023-01-19', '20.00', 19, 368),
(408, 5, '2023-01-19', '50.00', 19, 368),
(409, 2, '2023-01-19', '84.00', 13, 368);

--
-- Indexes for dumped tables
--

--
-- Indexes for table `book`
--
ALTER TABLE `book`
  ADD PRIMARY KEY (`BookID`);

--
-- Indexes for table `bookseller`
--
ALTER TABLE `bookseller`
  ADD PRIMARY KEY (`BooksellerID`);

--
-- Indexes for table `customer`
--
ALTER TABLE `customer`
  ADD PRIMARY KEY (`CustomerID`);

--
-- Indexes for table `purchase`
--
ALTER TABLE `purchase`
  ADD PRIMARY KEY (`PurchaseID`),
  ADD KEY `PURCHASE_BOOK_FK` (`BookID`),
  ADD KEY `PURCHASE_CUSTOMER_FK` (`CustomerID`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `book`
--
ALTER TABLE `book`
  MODIFY `BookID` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=28;

--
-- AUTO_INCREMENT for table `bookseller`
--
ALTER TABLE `bookseller`
  MODIFY `BooksellerID` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=3;

--
-- AUTO_INCREMENT for table `customer`
--
ALTER TABLE `customer`
  MODIFY `CustomerID` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=373;

--
-- AUTO_INCREMENT for table `purchase`
--
ALTER TABLE `purchase`
  MODIFY `PurchaseID` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=410;

--
-- Constraints for dumped tables
--

--
-- Constraints for table `purchase`
--
ALTER TABLE `purchase`
  ADD CONSTRAINT `PURCHASE_BOOK_FK` FOREIGN KEY (`BookID`) REFERENCES `book` (`BookID`),
  ADD CONSTRAINT `PURCHASE_CUSTOMER_FK` FOREIGN KEY (`CustomerID`) REFERENCES `customer` (`CustomerID`);
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
