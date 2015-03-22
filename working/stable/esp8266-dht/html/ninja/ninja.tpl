<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1, maximum-scale=1, user-scalable=no">
    <title>Ninja connection</title>

    <link href="../css/bootstrap.min.css" rel="stylesheet">

    <style type="text/css">
    body {
      padding-top: 70px;
    }
    .footer {
      background-color: #00cccc;
    }
    </style>
  </head>
  <body>
    <div class="container">
      <div class="jumbotron">
        <h1>Ninja Config</h1>
        <div id="main">
            <form name="ninjaform" action="ninja.cgi" method="post">
            <p>Put your Ninja Token here:</p> 
            <br />
            <input type="text" name="ninja_token" value="%ninja_token%" class="form-control"><br /><br />
            <input type="submit" name="connect" value="Save!" class="btn btn-lg btn-success">
        </div>
      </div>
    </div>
  </body>
 <script src="../js/jquery.min.js"></script>
 <script src="../js/bootstrap.min.js"></script>
</html>
