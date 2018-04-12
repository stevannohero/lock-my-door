<?php   
  // kalau di web hosting
  $con=mysqli_connect("localhost","id5368127_pbd_root","12345","id5368127_pbd");

  // kalau di lokal
  // $con=mysqli_connect("localhost","root","","fitness");
   if (mysqli_connect_errno($con)) {
      echo "Failed to connect to MySQL: " . mysqli_connect_error();
   }
	
   $result = mysqli_query($con, "SELECT password FROM pbd_passwords WHERE ID = 1");

   while ($row = mysqli_fetch_assoc($result)) {
     $array[] = $row;
   }

//   header('Content-Type:Application/text');

    $array_result = array(
            "info" => $array,
        );

   echo $array[0]["password"];  
//   echo json_encode($array_result);
 
   mysqli_free_result($result);
 
   mysqli_close($con);
