<html>
<head>
    <title>INPUT Pin status</title>
    <link rel="stylesheet" type="text/css" href="media/style.css">
    <script type="text/javascript" src="media/140medley.min.js"></script>

    <script type="text/javascript">

        var xhr=j();

        function generateInputTable(data) {
            var div=document.createElement("div");
            div.id="inputdiv";

            for(var i = 0; i < data.inputs.length; i++) {
                div.appendChild( generateInputRow( data.inputs[i] ) );
            }
            return div;
        }

        function generateInputRow(data) {
            var row=document.createElement("div");
            row.className="inputrow";
            // create label column
            var labelcell = document.createElement('div');
                labelcell.className="cell-label";
                labelcell.innerHTML = data.input;

            row.appendChild(labelcell);
            // create value column
            var valuecell=document.createElement("div");
                valuecell.className="cell-value cell-value-"+data.value;
            row.appendChild(valuecell);

            return row;
        }

        function getInputs() {
            xhr.open("GET", "showinputs.cgi");
            xhr.onreadystatechange=function() {
                if (xhr.readyState==4 && xhr.status>=200 && xhr.status<300) {
                    var data=JSON.parse(xhr.responseText);
                    if (data.result && data.result.inputs.length>1) {
                        $("#content").innerHTML = "";
                        $("#content").appendChild( generateInputTable(data.result) );
                        window.setTimeout(getInputs, 1000);
                    }
                }
            }
            xhr.send();
        }

        window.onload=function(e) {
            getInputs();
        };
    </script>
</head>
<body>
<div id="main">
    <div id="input-label">INPUT Pin status</div>
    <div id="input-list">
        <div class="inputrow"><div class="cell-label">LABEL</div><div class="cell-value">STATE</div></div>
        <div id="content"></div>
    </div>
</div>
</body>
</html>
