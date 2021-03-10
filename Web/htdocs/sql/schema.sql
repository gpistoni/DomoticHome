--
-- Table structure for table `registered_users`
--

CREATE DATABASE my_pistonihome;

USE DATABASE my_pistonihome;

CREATE TABLE `registered_users` (
  `id` int(8) NOT NULL,
  `user_name` varchar(255) NOT NULL UNIQUE,
  `display_name` varchar(255) NOT NULL UNIQUE,
  `password` varchar(255) NOT NULL,
  `email` varchar(255) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

ALTER TABLE `registered_users`
  ADD PRIMARY KEY (`id`);
  
ALTER TABLE `registered_users`
  MODIFY `id` int(8) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=4;

--
-- Dumping data for table `registered_users`
--
INSERT INTO `registered_users` (`id`, `user_name`, `display_name`, `password`, `email`) VALUES
(1, 'pistoni', 'pistoni', 'gpisto', 'mia@mail.com');

COMMIT;
