<?php
	// kalau di web hosting
  $con=mysqli_connect("localhost","id5368127_pbd_root","12345","id5368127_pbd");

	// kalau di lokal
	// $con=mysqli_connect("localhost","root","","fitness");
	if (mysqli_connect_errno($con)) {
		echo "Failed to connect to MySQL: ".mysqli_connect_error()."<br>";
	}

	$password = $_GET["password"];

  $query =  "UPDATE pbd_passwords SET password ='$password' WHERE ID = 1";

	mysqli_query($con, $query);	

  echo "hello world"; 
//		echo json_encode($response);
	mysqli_close($con); 
