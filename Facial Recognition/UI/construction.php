<?php
   include("connect.php");

session_start();
$username = $_SESSION['headname'];
  
  if($_SERVER["REQUEST_METHOD"] == "POST") {
      
  		if( $_POST['password'] == $_SESSION['userkey'] ){
  			  
  			  $_SESSION['tname'] = $_POST['firstName'];
		      $_SESSION['course'] = $_POST['course'];
		      $_SESSION['subject'] = $_POST['subject'];
		      $_SESSION['date'] = date("Y-m-d");

  			  $name = $_POST['firstName'];
		      $course = $_POST['course'];
		      $subject = $_POST['subject'];
		      $date = date("Y-m-d");
		      $sql = "INSERT INTO record (teacher, course, subject, date_l) VALUES ('$name', '$course', '$subject', '$date')";
      //echo $db->query($sql);
		      
	      if ($db->query($sql) === TRUE) {
			    //echo $db->query($sql);
	      	        $command = escapeshellcmd("python C:/Users/harsh/Desktop/DBA/project/spreadsheet.py ");
          $date1 = shell_exec($command);
 
			$command = escapeshellcmd("python C:/Users/harsh/Desktop/DBA/project/identify.py");
	   	 	$output = shell_exec($command);	
			echo "<meta http-equiv='refresh' content='1;url=result.php' />";
			} else {
			    echo "Error: " . $sql . "<br>" . $db->error;
			}
  		}
  		else{
  			 echo "Error: Password Invalid <br>" ;
  		}	
      

	 }

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
  <a href="add_student.php">Add Student</a>
  <a href="index.php">Log Out</a>
  <a href="#" onclick="closeNav()"><-</a>
</div>



<div class="row">
	<div class="m1 col-sm-8">
	<div class="container">
            <h2 style="text-align: center;">Attendance Submission</h2>
                
            <form class="form-horizontal" method="post"  role="form">
                <div class="form-group " >
                    <label for="firstName" class="col-sm-3 control-label">Name</label>
                    <div class="col-sm-9">
                        <input type="text" name="firstName"  placeholder="First Name" class="form-control" autofocus>
                    </div>
                </div>
                
                <div class="form-group " >
                    <label for="course" class="col-sm-3 control-label">Course Name</label>
                    <div class="col-sm-9">
                        <input type="text" name="course" placeholder="Course Name" class="form-control" autofocus>
                    </div>
                </div>
                
                <div class="form-group " >
                    <label for="subject" class="col-sm-3 control-label">Subject</label>
                    <div class="col-sm-9">
                        <input type="text" name="subject" placeholder="Subject" class="form-control" autofocus>
                    </div>
                </div>
                
                	
                <div class="form-group " >
                    <label for="photo" class="col-sm-3 control-label">Upload Photograph</label>
                    <div class="col-sm-9">
                        <input type="file" name="photo" placeholder="First Name" accept="image/*" class="form-control" >
                    </div>
                </div>
                <div class="form-group">
                    <label for="password" class="col-sm-3 control-label">Password*</label>
                    <div class="col-sm-9">
                        <input type="password" name="password" placeholder="Password" class="form-control">
                    </div>
                </div>
                
                <button type="submit" class="col-sm-2 btn btn-primary btn-block">Submit</button>
            </form> <!-- /form -->
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

