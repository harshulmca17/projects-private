<?php
   include("connect.php");

session_start();
$username = $_SESSION['headname'];
  
  if($_SERVER["REQUEST_METHOD"] == "POST") {
      
      if( $_POST['password'] == $_SESSION['userkey'] ){
        $name = $_POST['name'];
        $rolln = $_POST['rolln'];
        $_SESSION['mrolln'] = substr($rolln,-2);
        $subject = $_POST['subject'];
        $phone = $_POST['phone'];
        $sql = "INSERT INTO mca (roll_no, name, phone, subject) VALUES ($rolln, '$name', '$phone', '$subject')";

  		if ($db->query($sql) === TRUE) {
  		    
  			 $command = escapeshellcmd("python C:/Users/harsh/Desktop/DBA/project/add_student.py $name $rolln");
     	 		$output = shell_exec($command);
      
      		
  		    ?>
              <div class="alert alert-success" style="padding-left: 38%; " role="alert">
                 New student added successfull
              </div>
              
           <?php
  		} else {
          
            echo " <div class='alert alert-danger' style='padding-left: 18%; ' role='alert'>
                    Error: " . $sql . "<br>" . $db->error."</div>";
              
           
  		}
   }
   else{
       echo "<div class='alert alert-danger' style='padding-left: 38%; ' role='alert'>Error: Password Invalid <br></div>" ;
      
   }
 }

   if(isset($_GET['step2'])){
        $nrolln = $_SESSION['mrolln'];
        echo $nrolln;
        $command = escapeshellcmd("python C:/Users/harsh/Desktop/DBA/project/create_person.py user$nrolln");
        $output = shell_exec($command);
        echo $output;
   }

   if(isset($_GET['step3'])){
        $nrolln = $_SESSION['mrolln'];
        $command = escapeshellcmd("python C:/Users/harsh/Desktop/DBA/project/add_person_faces.py user$nrolln");
        $output = shell_exec($command);
        
   }
   if(isset($_GET['step4'])){
        $command = escapeshellcmd("python C:/Users/harsh/Desktop/DBA/project/train.py ");
        $output = shell_exec($command);
        
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
  <a href="construction.php">Upload Attendance</a>
  <a href="index.php">Log Out</a>
  <a href="#" onclick="closeNav()"><-</a>
</div>



<div class="row">
	<div class="m1 col-sm-6">
	
	 <div class="container">
         <h5 style="text-align: center;">Step 1 </h5>   
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
                        <input type="password" name="password" id="password" placeholder="Password" class="form-control">
                    </div>
              </div>
                
                <button type="submit" class="col-sm-2 btn btn-primary btn-block">Add </button>
            </form>
    </div>	
</div>
<div class="m1 col-sm-5">
  
   <div class="container">
        <h5 style="text-align: center;">Step 2 </h5>   
            <h3 style="text-align: center;">Create Personal Id</h3>
            <form action="" method="get">
              <button type="submit" name="step2" class="col-sm-2 btn btn-primary btn-block">Create</button>
            </form>
            <hr><hr>
        <h5 style="text-align: center;">Step 3 </h5>   
            <h3 style="text-align: center;">Add Student Face </h3>
            <form action="" method="get">
              <button type="submit" name="step3" class="col-sm-2 btn btn-primary btn-block">Add</button>
            </form>
            <hr><hr>
        <h5 style="text-align: center;">Step 4 </h5>   
            <h3 style="text-align: center;">Submit Change To Model</h3>    
            <form action="" method="get">
              <button type="submit" name="step4" class="col-sm-2 btn btn-primary btn-block">Submit</button>
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

