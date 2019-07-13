<?php
	$name = "SUSHI";
	$nrolln = "55";
    //$output = substr($rolln,-2);
    //$output = sprintf("user%s.",$output);
    //$command = escapeshellcmd("python C:/Users/harsh/Desktop/DBA/project/add_student.py $name $rolln");
    //$output = shell_exec($command);
    $filePath = realpath($_FILES["file"]["tmp_name"]);
    echo  $filePath;
    //echo $output;
?>
