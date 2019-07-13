<?php
   include("connect.php");

session_start();
$username = $_SESSION['headname'];
  
        $name =  $_SESSION['tname'];
        $course =   $_SESSION['course'];
        $subject =   $_SESSION['subject'];
        $date =   $_SESSION['date'];

        $command = escapeshellcmd("python C:/Users/harsh/Desktop/DBA/project/result.py ");
          $present_student = shell_exec($command);
        $command = escapeshellcmd("python C:/Users/harsh/Desktop/DBA/project/total.py ");
          $total_student = shell_exec($command);
        $command = escapeshellcmd("python C:/Users/harsh/Desktop/DBA/project/absent.py ");
          $absent_student = shell_exec($command);
        $command = escapeshellcmd("python C:/Users/harsh/Desktop/DBA/project/date.py ");
          $date1 = shell_exec($command);

        $link = sprintf("python C:/Users/harsh/Desktop/DBA/project/reports%s.xlsx",$date1);
?>

<!DOCTYPE html>
<html>
<head>
<title>Dashboard </title>

<link href="css/bootstrap.min.css" rel="stylesheet" id="bootstrap-css">
<link href="css/construction.css" rel="stylesheet" id="bootstrap-css">

<script src="js/bootstrap.min.js"></script>
<script src="js/jquery.min.js"></script>
<style type="text/css">
	:root {
  padding-top:6rem; 
}

</style>

</head>
<body>
	<nav class="navbar navbar-expand-sm bg-dark navbar-dark fixed-top">
  <div id="main">
  <img src="media/img_avatar.png" onclick="openNav()" alt="Avatar">
  </div>
  <a class="navbar-brand" href="index.php">Demo </a>
  <ul class="navbar-nav navbar-right">
    <li class="nav-item">
      <a class="nav-link" href="construction.php">Home</a>
    </li>
   
    <li class="nav-item">
      <a class="nav-link" href="construction.php">About Us</a>
    </li>
    <li class="nav-item">
      <a class="nav-link" href="index.php">Logout</a>
    </li>
  </ul>

</nav>
<div id="mySidebar" class="sidebar">
  <h4 ><?php echo $username; ?></h4>
  <a href="schedule.pdf" target="_blank">Schedule</a>
  <a href="construction.php" target="_blank">Upload Attendance</a>
  <a href="index.php">Log Out</a>
  <a href="#" onclick="closeNav()"><-</a>
</div>



<div class="row">
	<div class="m1 col-sm-8">
	<div class="container" style="padding-left: 10%; padding-right: 10%; padding-bottom: 5%; padding-top: 5%;">
  <table class="table table-striped">
  <thead>
    <tr>
            <th style="text-align: center;">Attendance Result</th>
      
    </tr>
  </thead>
  <tbody>
    <tr>
          <td >Teacher :        <?php echo $name; ?></td>
    </tr>
    <tr>
              <td >Subject :        <?php echo $subject; ?></td>
      
    </tr>
    <tr>
      
              <td >Course :         <?php echo $course; ?></td>
    </tr>
    <tr>
      
              <td >Date :           <?php echo $date; ?></td>
    </tr>
    <tr>
              <td >Total Student Enrolled : <?php echo $total_student; ?></td>
      
    </tr>
    <tr>
      
              <td >Student Present :        <?php echo $present_student; ?></td>
    </tr>
    <tr>
      
              <td >Student Absent :          <?php echo $absent_student; ?></td>
    </tr>
    <tr>
      
              <td style="text-align: center;"><a href="reports15_04_19.xlsx" class="btn btn-primary"  download>Download Attendance Sheet</a></td>
    </tr>
  </tbody>
</table>
              
             <!-- /form -->
        </div> <!-- ./container -->

</div>
	
</div>

	
<script>
function openNav() {
  document.getElementById("mySidebar").style.width = "180px";
  document.getElementById("main").style.marginLeft = "180px";
}

function closeNav() {
  document.getElementById("mySidebar").style.width = "0";
  document.getElementById("main").style.marginLeft= "0";
}
</script>
</body>
</html>
<!------ Include the above in your HEAD tag ---------->

