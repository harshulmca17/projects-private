<?php
   include("connect.php");
   session_start();
   
   if($_SERVER["REQUEST_METHOD"] == "POST") {
      // username and password sent from form 
      $_SESSION['headname'] = $_POST['username'];
      $_SESSION['userkey'] = $_POST['password'];
      $myusername = mysqli_real_escape_string($db,$_POST['username']);
      $mypassword = mysqli_real_escape_string($db,$_POST['password']); 
      
      $sql = "SELECT id FROM admin WHERE username = '$myusername' and password = '$mypassword'";
      $result = mysqli_query($db,$sql);
      $row = mysqli_fetch_array($result,MYSQLI_ASSOC);
      $active = $row['active'];
      
      $count = mysqli_num_rows($result);
      
      // If result matched $myusername and $mypassword, table row must be 1 row
      
      if($count == 1) {
         ?>
            <div class="alert alert-success" style="padding-left: 68%; " role="alert">
               Log In Successfull
            </div>
            <meta http-equiv="refresh" content="3;url=construction.php" />
         <?php
        // header("location: construction.php");
      }else {
         ?>
            <div class="alert alert-danger" style="padding-left: 68%; " role="alert">
               Your Login Name or Password is invalid
            </div>
         <?php
         
      }
   }
?>

<!DOCTYPE html>
<html>
<head>


<link href="//maxcdn.bootstrapcdn.com/bootstrap/4.0.0/css/bootstrap.min.css" rel="stylesheet" id="bootstrap-css">
<script src="//maxcdn.bootstrapcdn.com/bootstrap/4.0.0/js/bootstrap.min.js"></script>
<script src="//code.jquery.com/jquery-1.11.1.min.js"></script>
<link href="css/new.css" rel="stylesheet" id="bootstrap-css">
   <title>Log In</title>
</head>
<body>
<div class="sidenav">
         <div class="login-main-text">
            <h2>Online <br> Attendance Submission</h2>
            <p>Login or register from here to access.</p>
         </div>
      </div>
      <form action = "" method = "post">
         <div class="main">
            <div class="col-md-6 col-sm-12">
               <div class="login-form">
                  <form>
                     <div class="form-group">
                        <label>User Name</label>
                        <input type="text" class="form-control" name="username" placeholder="User Name">
                     </div>
                     <div class="form-group">
                        <label>Password</label>
                        <input type="password" name="password" class="form-control" placeholder="Password">
                     </div>
                     <button type="submit" class="btn btn-black">Login</button>
                     <button type="submit" class="btn btn-secondary">Register</button>
                  </form>
               </div>
            </div>
         </div>
      </form>
</body>
</html>
<!------ Include the above in your HEAD tag ---------->
