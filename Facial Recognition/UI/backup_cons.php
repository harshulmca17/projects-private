<?php
   include("connect.php");

session_start();
$username = $_SESSION['headname'];
  
  if($_SERVER["REQUEST_METHOD"] == "POST") {
      
      $name = $_POST['name'];
      $rolln = $_POST['rolln'];
      $subject = $_POST['subject'];
      $phone = $_POST['phone'];
      $sql = "INSERT INTO mca (roll_no, name, phone, subject) VALUES ($rolln, '$name', '$phone', '$subject')";

		if ($db->query($sql) === TRUE) {
		    
			$command = escapeshellcmd("python C:/Users/harsh/Desktop/DBA/project/add_student.py $name $rolln");
   	 		$output = shell_exec($command);
    
    		echo $output;
		    ?>
            <div class="alert alert-success" style="padding-left: 38%; " role="alert">
               New student added successfull
            </div>
            
         <?php
		} else {
		    echo "Error: " . $sql . "<br>" . $db->error;
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
	<div class="m1 col-sm-6">
	<div class="container">
            <h2 style="text-align: center;">Attendance Submition</h2>
                
            <form class="form-horizontal"  role="form">
                <div class="form-group " >
                    <label for="firstName" class="col-sm-3 control-label">Name</label>
                    <div class="col-sm-9">
                        <input type="text" id="firstName" placeholder="First Name" class="form-control" autofocus>
                    </div>
                </div>
                
                <div class="form-group " >
                    <label for="course" class="col-sm-3 control-label">Course Name</label>
                    <div class="col-sm-9">
                        <input type="text" id="course" placeholder="Course Name" class="form-control" autofocus>
                    </div>
                </div>
                
                <div class="form-group " >
                    <label for="subject" class="col-sm-3 control-label">Subject</label>
                    <div class="col-sm-9">
                        <input type="text" id="subject" placeholder="subject" class="form-control" autofocus>
                    </div>
                </div>
                
                	
                <div class="form-group">
                    <label for="birthDate" class="col-sm-3 control-label">Date</label>
                    <div class="col-sm-9">
                        <input type="date" id="birthDate" class="form-control">
                    </div>
                </div>
                <div class="form-group " >
                    <label for="firstName" class="col-sm-3 control-label">Upload Photograph</label>
                    <div class="col-sm-9">
                        <input type="file" id="firstName" placeholder="First Name" accept="image/*" class="form-control" >
                    </div>
                </div>
                <div class="form-group">
                    <label for="password" class="col-sm-3 control-label">Password*</label>
                    <div class="col-sm-9">
                        <input type="password" id="password" placeholder="Password" class="form-control">
                    </div>
                </div>
                
                <button type="submit" class="col-sm-2 btn btn-primary btn-block">Submit</button>
            </form> <!-- /form -->
        </div> <!-- ./container -->

</div>
	<div class="m1 col-sm-5">
	<div class="container">
            <h2 style="text-align: center;">Add Student</h2>
    		<form class="form-horizontal"  role="form" method="post">
                <div class="form-group " >
                    <label for="name" class="col-sm-3 control-label">Name</label>
                    <div class="col-sm-9">
                        <input type="text" name="name" id="name" placeholder="First Name" class="form-control" autofocus>
                    </div>
                </div>
                
				<div class="form-group " >
                    <label for="rolln" class="col-sm-3 control-label">Roll No.</label>
                    <div class="col-sm-9">
                        <input type="text" id="rolln" name="rolln" placeholder="Roll No." class="form-control" autofocus>
                    </div>
                </div>
                
                <div class="form-group " >
                    <label for="phone" class="col-sm-3 control-label">Phone No.</label>
                    <div class="col-sm-9">
                        <input type="text" name="phone" id="phone" placeholder="Phone No." class="form-control" autofocus>
                    </div>
                </div>

                
                
                <div class="form-group " >
                    <label for="course" class="col-sm-4 control-label">Course Name</label>
                    <div class="col-sm-9">
                        <input type="text" id="course" name="course" placeholder="Course Name" class="form-control" autofocus>
                    </div>
                </div>
                
                <div class="form-group " >
                    <label for="subject" class="col-sm-3 control-label">Subject</label>
                    <div class="col-sm-9">
                        <input type="text" id="subject" name="subject" placeholder="Subject" class="form-control" autofocus>
                    </div>
                </div>
                
                	
               <div class="form-group">
                    <label for="password" class="col-sm-3 control-label">Password*</label>
                    <div class="col-sm-9">
                        <input type="password" id="password" placeholder="Password" class="form-control">
                    </div>
              </div>
                
                <button type="submit" class="col-sm-2 btn btn-primary btn-block">Add </button>
            </form>
    </div>	
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

