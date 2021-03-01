<?php

$x =  $_GET['myvar'];


INSERT INTO `wattage` (`DT`, `Produced`, `Consumed`, `L1`, `L2`, `L3`) VALUES (CURRENT_TIME(), '1', '2', '3', '4', '5') 


?> 

<html>
<head>
<title>User Login</title>
<link href="./view/css/style.css" rel="stylesheet" type="text/css" />
</head>
<body>
    <div>
        <div class="dashboard">
            <div class="member-dashboard">
			myvar: <?php echo $x; ?> 
            </div>
        </div>
    </div>
</body>
</html>