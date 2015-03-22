<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1, maximum-scale=1, user-scalable=no">
    <title>WiFi connection</title>

    <link href="../css/bootstrap.min.css" rel="stylesheet">

    <style type="text/css">
    body {
      padding-top: 70px;
    }
    .footer {
      background-color: #00cccc;
    }
    .icon {
        background-image: url("icons.png");
        background-color: transparent;
        width: 32px;
        height: 32px;
        display: inline-block;
    }
    </style>
  </head>
  <body>
    <div class="container">
      <div class="jumbotron">
        <h1>WiFi connection</h1>
        <div id="main">
            <p>Current WiFi mode: <span class="badge"><b>%WiFiMode%</b></p>
            <form name="wifiform" action="connect.cgi" method="post">
            <p>To connect to a WiFi network, please select one of the detected networks...<br />
                <div id="aps" class="alert alert-success">Scanning...</div>
                <br />
                WiFi password, if applicable: <br />
                <label for="passwd"><input type="text" id="label" name="passwd" val="%WiFiPasswd%" class="form-control"></label> 
                <input type="submit" name="connect" value="Connect!" class="btn btn-lg btn-success">
            </p>
        </div>
      </div>
    </div>
  </body>

 <script src="../js/jquery.min.js"></script>
 <script src="../js/bootstrap.min.js"></script>
 <script type="text/javascript">$(document).ready(function () {});</script>
<!-- <script type="text/javascript" src="140medley.min.js"></script>-->

 <script type="text/javascript">

 var t=function(d,c){return function(b,a){return d.replace(/#{([^}]*)}/g,function(e,g){return Function("x","with(x)return "+g).call(b,a||c||{})})}},s=function(d,c){return c?{get:function(a){return d[a]&&c.parse(d[a])},set:function(b,a){d[b]=c.stringify(a)}}:{}}(this.localStorage||{},JSON),p=function(f,e,h,g){h=h||document;g=h[e="on"+e];f=h[e]=function(a){g=g&&g(a=a||h.event);return(f=f&&e(a))?e:g};h=this},m=function(e,d,f){d=document;f=d.createElement("p");f.innerHTML=e;for(e=d.createDocumentFragment();d=f.firstChild;){e.appendChild(d)}return e},$=function(d,c){d=d.match(/^(\W)?(.*)/);return(c||document)["getElement"+(d[1]?d[1]=="#"?"ById":"sByClassName":"sByTagName")](d[2])},j=function(d){for(d=0;d<4;d++){try{return d?new ActiveXObject([,"Msxml2","Msxml3","Microsoft"][d]+".XMLHTTP"):new XMLHttpRequest}catch(c){}}};

 </script>

 <script type="text/javascript">

var xhr=j();
var currAp="%currSsid%";
var currIp="%currIp%";

function createInputForAp(ap) {
	if (ap.essid=="" && ap.rssi==0) return;
	var div=document.createElement("div");
	div.id="apdiv";


    var rssi=document.createElement("div");
    var rssiVal=-Math.floor(ap.rssi/5)*32;
    rssi.className="icon";
    rssi.style.backgroundPosition="0px "+rssiVal+"px";
    rssi.style.margin="0px 0px 0px 2px";
    var encrypt=document.createElement("div");
    var encVal="-64"; //assume wpa/wpa2
    if (ap.enc=="0") encVal="0"; //open
    if (ap.enc=="1") encVal="-32"; //wep
    encrypt.className="icon";
    encrypt.style.backgroundPosition="-32px "+encVal+"px";

	var input=document.createElement("input");
	input.type="radio";
	input.name="essid";
	input.value=ap.essid;
    var label=document.createElement("label");
	if (currAp==ap.essid) {
        input.checked="1";
        label.textContent=ap.essid+" (IP Address: "+currIp+")";
    } else {
        label.textContent=ap.essid;
    }
	input.id="opt-"+ap.essid;
	label.htmlFor="opt-"+ap.essid;
	div.appendChild(input);

    div.appendChild(rssi);
    div.appendChild(encrypt);
    
	div.appendChild(label);
	return div;
}

function getSelectedEssid() {
	var e=document.forms.wifiform.elements;
	for (var i=0; i<e.length; i++) {
		if (e[i].type=="radio" && e[i].checked) return e[i].value;
	}
	return currAp;
}

function scanAPs() {
	xhr.open("GET", "wifiscan.cgi");
	xhr.onreadystatechange=function() {
		if (xhr.readyState==4 && xhr.status>=200 && xhr.status<300) {
			var data=JSON.parse(xhr.responseText);
			currAp=getSelectedEssid();
			if (data.result.inProgress=="0" && data.result.APs.length>1) {
				$("#aps").innerHTML="";
				for (var i=0; i<data.result.APs.length; i++) {
					if (data.result.APs[i].essid=="" && data.result.APs[i].rssi==0) continue;
					$("#aps").appendChild(createInputForAp(data.result.APs[i]));
				}
				window.setTimeout(scanAPs, 20000);
			} else {
				window.setTimeout(scanAPs, 1000);
			}
		}
	}
	xhr.send();
}

window.onload=function(e) {
	scanAPs();
};
</script>
</head>
</html>
