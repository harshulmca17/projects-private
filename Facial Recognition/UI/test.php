<?php 
		$command = escapeshellcmd('python C:/Users/harsh/Desktop/DBA/project/detect.py C:/Users/harsh/Desktop/DBA/project/pics/test14.JPG ');
   	 	$output = shell_exec($command);	
		echo $output;  
		echo "2";
?>
