const char* LoginPage =
  "<html>"
  "<head>"
  "<style>"
  "body { font-family: Arial, sans-serif; background-color: #F2F2F2; }"
  "form { width: 30%; margin: auto; background-color: #FFFFFF; padding: 20px; border-radius: 10px; box-shadow: 0 4px 8px rgba(0,0,0,0.1); }"
  "h2 { text-align: center; color: #333333; }"
  "label { display: block; margin: 10px 0; }"
  "input { width: 100%; padding: 10px; margin-bottom: 15px; box-sizing: border-box; }"
  "input[type='submit'] { background-color: #4CAF50; color: white; border: none; border-radius: 5px; cursor: pointer; }"
  "</style>"
  "</head>"
  "<body>"
  "<form name='loginForm'>"
  "<h2>Clock Login Page</h2>"
  "<label for='userid'>Username:</label>"
  "<input type='text' id='userid' name='userid'>"
  "<label for='pwd'>Password:</label>"
  "<input type='password' id='pwd' name='pwd'>"
  "<input type='submit' value='Login' onclick='check(this.form)'>"
  "</form>"
  "<script>"
  "function check(form) {"
  "  if(form.userid.value=='admin' && form.pwd.value=='admin') {"
  "    window.open('/landingPage');"
  "  } else {"
  "    alert('Error: Incorrect Password or Username');"
  "  }"
  "}"
  "</script>"
  "</body>"
  "</html>";

/*
 * Server Index Page
 */

const char* landingPage =
  "<html>" 
  "<head>"
  "<script src='https://ajax.googleapis.com/ajax/libs/jquery/3.2.1/jquery.min.js'></script>"
  "<style>"
  "body { font-family: Arial, sans-serif; background-color: #F2F2F2; margin: 0; }"
  "form { width: 30%; margin: auto; background-color: #FFFFFF; padding: 20px; border-radius: 10px; box-shadow: 0 4px 8px rgba(0,0,0,0.1); }"
  "input[type='file'] { margin-bottom: 10px; }"
  "#prgContainer { width: 30%; margin: auto; background-color: #FFFFFF; border-radius: 5px; overflow: hidden; display: none; margin-top: 20px; margin-bottom: 20px; }"
  "#prg { width: 0%; background-color: #4CAF50; color: white; padding: 8px; text-align: center; transition: width 0.3s ease-in-out; }"
  "</style>"
  "</head>"
  "<body>"
  "<form method='POST' action='#' enctype='multipart/form-data' id='upload_form'>"
  "<input type='file' name='update'>"
  "<input type='submit' value='Update' onclick='showProgressBar()'>"
  "</form>"
  "<div id='prgContainer'>"
  "  <div id='prg'>0%</div>"
  "</div>"
  "<script>"
  "function showProgressBar() {"
  "  $('#prgContainer').show();"
  "  $('form').submit(function(e) {"
  "    e.preventDefault();"
  "    var form = $('#upload_form')[0];"
  "    var data = new FormData(form);"
  "    $.ajax({"
  "      url: '/update',"
  "      type: 'POST',"
  "      data: data,"
  "      contentType: false,"
  "      processData: false,"
  "      xhr: function() {"
  "        var xhr = new window.XMLHttpRequest();"
  "        xhr.upload.addEventListener('progress', function(evt) {"
  "          if (evt.lengthComputable) {"
  "            var per = evt.loaded / evt.total;"
  "            $('#prg').html(Math.round(per*100) + '%');"
  "            $('#prg').css('width', Math.round(per*100) + '%');"
  "          }"
  "        }, false);"
  "        return xhr;"
  "      },"
  "      success: function(d, s) {"
  "        console.log('success!');"
  "      },"
  "      error: function(a, b, c) {"
  "      }"
  "    });"
  "  });"
  "}"
  "</script>"
  "</body>"
  "</html>";



/*
 * setup function
 */
void OTAsetup() {
  /*use mdns for host name resolution*/
  if (!MDNS.begin(host)) {  //http://esp32.local
    Serial.println("Error setting up MDNS responder!");
    while (1) {
      delay(1000);
    }
  }
  Serial.println("mDNS responder started");
  /*return index page which is stored in serverIndex */
  server.on("/", HTTP_GET, []() {
    server.sendHeader("Connection", "close");
    server.send(200, "text/html", LoginPage);
  });
  server.on("/landingPage", HTTP_GET, []() {
    server.sendHeader("Connection", "close");
    server.send(200, "text/html", landingPage);
  });
  /*handling uploading firmware file */
  server.on(
    "/update", HTTP_POST, []() {
      server.sendHeader("Connection", "close");
      server.send(200, "text/plain", (Update.hasError()) ? "FAIL" : "OK");
      ESP.restart();
    },
    []() {
      HTTPUpload& upload = server.upload();
      if (upload.status == UPLOAD_FILE_START) {
        Serial.printf("Update: %s\n", upload.filename.c_str());
        if (!Update.begin(UPDATE_SIZE_UNKNOWN)) {  //start with max available size
          Update.printError(Serial);
        }
      } else if (upload.status == UPLOAD_FILE_WRITE) {
        /* flashing firmware to ESP*/
        if (Update.write(upload.buf, upload.currentSize) != upload.currentSize) {
          Update.printError(Serial);
        }
      } else if (upload.status == UPLOAD_FILE_END) {
        if (Update.end(true)) {  //true to set the size to the current progress
          Serial.printf("Update Success: %u\nRebooting...\n", upload.totalSize);
        } else {
          Update.printError(Serial);
        }
      }
    });
  server.begin();
}