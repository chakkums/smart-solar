var scanSuccess = function(result) {
    var textFormats = "QR_CODE";
    if (result.cancelled) { return; }

    if (textFormats.match(result.format)) {
        if (result.text.indexOf("http") !== 0) {
            document.getElementById("information").innerHTML = "Loading battery data from remote server...<br/><br/><br/>";
            window.location.replace("batteryInfo.html#"+result.text);
        }else{
            document.getElementById("information").innerHTML = "Error: URL detected. <br/> Please scan a battery.<br/><br/><br/>";
        }
    }else{
        document.getElementById("information").innerHTML = "Error: Barcode is not QR type.<br/> Please scan a battery.<br/><br/><br/>";
    }
}

var scanCode = function() {
    window.plugins.barcodeScanner.scan(
        scanSuccess,
        function(error) {
            alert("Scan failed: " + error);
        });
}

var returnToScan = function() {
    window.location.replace("index.html");
}