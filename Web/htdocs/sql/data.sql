CREATE TABLE IF NOT EXIST `Wattage` (
 `id` int PRIMARY KEY  AUTO_INCREMENT,
 `Dt` datetime NOT NULL,
 `Produced` int,
 `Consumed` int,
 `SelfConsumed` int,
 `Surplus` int, 
 `L1` int, 
 `L2` int, 
 `L3` int );

  
CREATE VIEW `Wattage_month` AS 
SELECT MONTH(DATE) + '.' + YEAR(DATE) AS Day, 
AVG(`Produced`) AS Produced,
AVG(`Consumed`) AS Consumed,
AVG(`L1`) AS L1, 
AVG(`L2`) AS L2, 
AVG(`L3`) AS L3 
FROM `Wattage` 
WHERE 1 
GROUP BY MONTH(DATE),YEAR(DATE) ;

CREATE VIEW `Wattage_day` AS 
SELECT CAST(`Dt` as DATE) AS Day, 
AVG(`Produced`) AS Produced,
AVG(`Consumed`) AS Consumed,
AVG(`L1`) AS L1, 
AVG(`L2`) AS L2, 
AVG(`L3`) AS L3 
FROM `Wattage` 
WHERE 1 
GROUP BY CAST(`Dt` as DATE);

CREATE VIEW `Wattage_dayh` AS 
SELECT CAST(`Dt` as DATETIME) AS Day, 
AVG(`Produced`) AS Produced,
AVG(`Consumed`) AS Consumed,
AVG(`L1`) AS L1, 
AVG(`L2`) AS L2, 
AVG(`L3`) AS L3 
FROM `Wattage` 
WHERE 1 
GROUP BY HOUR(`Dt`), DAY(`Dt`);

CREATE VIEW `Wattage_dayh4` AS 
SELECT CAST(`Dt` as DATETIME) AS Day, 
AVG(`Produced`) AS Produced,
AVG(`Consumed`) AS Consumed,
AVG(`L1`) AS L1, 
AVG(`L2`) AS L2, 
AVG(`L3`) AS L3 
FROM `Wattage` 
WHERE 1 
GROUP BY FLOOR( HOUR(`Dt`) / 4 ), DAY(`Dt`);



