CREATE TABLE `Wattage` (
 `DT` datetime NOT NULL,
 `Produced` int NOT NULL,
 `Consumed` int NOT NULL,
 `L1` int, 
 `L2` int, 
 `L3` int ) 
 ENGINE=InnoDB DEFAULT CHARSET=latin1;

ALTER TABLE `registered_users`
  ADD PRIMARY KEY (`id`);

--
-- Dumping data for table `registered_users`
--
INSERT INTO `wattage` (`DT`, `Produced`, `Consumed`, `L1`, `L2`, `L3`) VALUES (CURRENT_TIME(), '1', '2', '3', '4', '5') 

COMMIT;
