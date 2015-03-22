<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1, maximum-scale=1, user-scalable=no">
    <title>Responsive UI for ESP8266</title>
    <link href="css/bootstrap.min.css" rel="stylesheet">
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
    <nav class="navbar navbar-default navbar-fixed-top" role="navigation">
      <div class="container">
        <div id="navbar" class="navbar-collapse collapse">
          <ul class="nav navbar-nav">
            <li class="active"><a href="#">Home</a></li>
          </ul>
          <ul class="nav navbar-nav navbar-right">
            <li><a href="/wifi">WLAN Config</a></li>
          </ul>
        </div>
      </div>
    </nav>
    <div class="container">
      <div class="jumbotron">
        <h1>Simple HTML Page using Bootstrap </h1>
	<a href="/wifi" class="btn btn-primary btn-lg btn-block">WLAN Config</a>
      </div>
    </div> <!-- /container -->

<nav class="navbar navbar-default navbar-fixed-bottom" role="navigation">
  <div class="container">
     <ul class="nav navbar-nav navbar-left">
	<li><a>footer</a></li>
      </ul>
  </div>
</nav>

<script src="js/jquery.min.js"></script>
<script src="js/bootstrap.min.js"></script>
</body>
</html>
