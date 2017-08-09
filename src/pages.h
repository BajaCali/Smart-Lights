typedef enum {
    MAIN = 1,
    LEDS = 2,
    LEDS_CONFIGURATOR = 3
} page;

page current_page = MAIN;

void main_switch(char* input);
String main_page();
void LEDS_switch(char* input);
String LEDS_page();
void LEDS_configurator_switch(char* input);
String LEDS_configurator_page();
String header();

String style_sheet(){
    String Page;
    Page += "\n<style type=\"text/css\">";
    Page += "\nh1 {font-family: Garamond; font-style: italic; font-size: 80px}";
    Page += "\nhr {border: none; border-top: medium double white}";
    Page += "\n</style>";
    return Page;
}

String header(){
    String Page;
    Page += "\nHTTP/1.1 200 OK";
    Page += "\nContent-Type: text/html";
    Page += "\nConnection: close";  // the connection will be closed after completion of the response
    Page += "\n";
    Page += "\n<!DOCTYPE HTML><html><head>";
    Page += "\n<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"></head>";
    Page += "\n<link rel=\"stylesheet\" type=\"text/css\" href=\"css.css\">";
    Page += "\n<title>Smart Lights</title>";
    Page += "\n<h1>Smart Lights</h1>";
    Page += "\n<hr border: none; border-top: medium double white>";
    return Page;
}

String ending(){
    String Page;
    Page += "\n</html>";
    return Page;
}

void switcher(page page, char* input){
    main_switch(input);
    switch(page){
        case MAIN:
        main_switch(input);
        break;
        case LEDS:
        LEDS_switch(input);
        break;
        case LEDS_CONFIGURATOR:
        LEDS_configurator_switch(input);
        break;
    }
}

String show_page(page page){
    String Page = header() + style_sheet();
    switch(page){
        case 1:
        Page += main_page();
        break;
        case 2:
        Page += LEDS_page();
        break;
        case 3:
        Page += LEDS_configurator_page();
    }
    return Page + ending();
}

void main_switch(char* input){
    if(strstr(input,"GET /MAIN_page")){
        current_page = MAIN;
        Serial.println("Going to MAIN_page");
    }
    else if (strstr(input,"GET /LEDS_configurator_page") > 0){
        current_page = LEDS_CONFIGURATOR;
        Serial.println("Going to LED_configurator_page");
    }
    else if (strstr(input,"GET /LEDS") > 0){
        current_page = LEDS;
        Serial.println("Going to LEDS_page");
    }
    else if(strstr(input,"GET /off") > 0){
        Serial.println("off");
    }
}

String main_page(){
    String Page;
    // Page += "\n<h1>What a nice colours!</h1>";
    Page += "\n<h6>We've already added a new code</h6>";
    Page += "\n<p><a href=\"LEDS\"><button>LEDS</button></a>&nbsp;</p>";
    // Page += "\n<p>LED #2 <a href=\"on2\"><button>ON</button></a>&nbsp;<a href=\"off2\"><button>OFF</button></a></p>";
    return Page;
}

void LEDS_switch(char* input){
    if (strstr(input,"GET /counter") > 0){
        counter();
        Serial.println("cnt++");
    }
    else if(strstr(input,"GET /off") > 0){
        LedBrs = 0;
        cnt = 0;
        Serial.println("off");
    }
}

String LEDS_page(){
    String Page;
    Page += "\n<a href=\"MAIN_page\"><button>MAIN Page</button></a>";
    Page += "\nMust Try! <a href=\"LEDS_configurator_page\"><button>Custom Configurator</button></a>";
    Page += "\n<h3>What a nice colours!</h3>";
    Page += "\nMODE: ";
    char tmp [3];
    itoa(cnt, tmp, 10);
    Page += tmp;
    Page += "\n<p>Change MODE or turn Off <a href=\"counter\"><button>CHANGE</button></a>&nbsp;<a href=\"off\"><button>OFF</button></a></p>";
    return Page;
}

int find_int_in_string(char* input, char* start, char* end){
    std::string config(input);
    size_t start_idx = config.find(start)+strlen(start);
    size_t end_idx = config.find(end);
    std::string red_str = config.substr(start_idx, end_idx);
    return std::stoi(red_str);
}

void LEDS_configurator_switch(char* input){  // buffer: GET /LEDS_configurator_page?red=80&green=80&blue=80 HTTP/1.1
    if((millis() - timeHigh) > minDifTime){
        cnt = 101;
        if (strstr(input, "red=") > 0){
            R = find_int_in_string(input, "red=", "&green");
            G = find_int_in_string(input, "green=", "&blue");
            B = find_int_in_string(input, "blue=", " HTTP");
            printf("\n R = %d, G = %d, B = %d", R, G, B);
            con_RGBxHSV = 0;
        }
        if (strstr(input, "cnt=") > 0){
            cnt = find_int_in_string(input, "cnt=", " HTTP");
        }
        if (strstr(input, "hue=") > 0){
            H = find_int_in_string(input, "hue=", "&saturate");
            S = find_int_in_string(input, "saturate=", "&value");
            LedBrs = find_int_in_string(input, "value=", " HTTP");
            printf("\n R = %d, G = %d, B = %d", R, G, B);
            con_RGBxHSV = 1;
        }
        if (strstr(input, "GET /breath") > 0){
            if (con_breath == 0)
                con_breath = 1;
            else
                con_breath = 0;
            if(con_RGBxHSV == 0)
                con_RGBxHSV = 1;
        }
        if (strstr(input, "GET /color") > 0){
            if (con_Color == 0)
                con_Color = 1;
            else
                con_Color = 0;
            if(con_RGBxHSV == 0)
                con_RGBxHSV = 1;
        }
    }
    timeHigh = millis();
}

String LEDS_configurator_page(){
    String Page;
    Page += "\n<a href=\"MAIN_page\"><button>MAIN Page</button></a>&nbsp;<a href=\"LEDS\"><button>Back</button></a>";
    Page += "\n<h3>What a nice colours!</h3>";
    Page += "\n<form><p>Set MODE <input name=\"cnt\" type=\"number\" min=\"0\" max=\"31\" value=\"" + String(cnt) + "\"><input type=\"submit\" value=\"Send\"></p></form>";
    Page += "<h5>RGB LED</h5>";
    Page += "<form><p2>";
    Page += "\n<a style=\"width:20%;color: red\"><b>RED</b></a>  <a style=\"width:15%;\" ><input name=\"red\" type=\"number\" min=\"0\" max=\"255\" step=\"1\" value=\"" + String(R) + "\" ></a><a style=\"width:27%;\"> </a>";
    Page += "\n<a style=\"width:20%;color: green\"><b>GREEN</b></a> <a style=\"width:15%;\" ><input name=\"green\" type=\"number\" min=\"0\" max=\"255\" step=\"1\" value=\"" + String(G) + "\"></a><a style=\"width:27%;\"> </a>";
    Page += "\n<a style=\"width:20%;color: blue\"><b>BLUE</b></a> <a style=\"width:15%;\" ><input name=\"blue\" type=\"number\" min=\"0\" max=\"255\" step=\"1\" value=\"" + String(B) + "\"></a><a style=\"width:27%;\"> </a>";
    Page += "</p2>";
    Page += "<p><a style=\"width:38%;\"></a> <a style=\"width:20%;\">         </a>   <label style=\"width:15%;\" ><input type=\"submit\" value=\"Send\"></label><a style=\"width:27%;\"></a></p>";
    Page += "</form>";
        Page += "<h5>HSV LED</h5>";
    Page += "<form><p2>";
    Page += "\n<a style=\"width:20%;><b>Hue</b></a>  <a style=\"width:15%;\" ><input name=\"hue\" type=\"number\" min=\"0\" max=\"255\" step=\"1\" value=\"" + String(H) + "\" ></a><a style=\"width:27%;\"> </a>";
    Page += "\n<a style=\"width:20%;><b>Saturate</b></a> <a style=\"width:15%;\" ><input name=\"saturate\" type=\"number\" min=\"0\" max=\"255\" step=\"1\" value=\"" + String(S) + "\"></a><a style=\"width:27%;\"> </a>";
    Page += "\n<a style=\"width:20%;><b>Value</b></a> <a style=\"width:15%;\" ><input name=\"value\" type=\"number\" min=\"0\" max=\"255\" step=\"1\" value=\"" + String(LedBrs) + "\"></a><a style=\"width:27%;\"> </a>";
    Page += "</p2>";
    Page += "<p><a style=\"width:38%;\"></a> <a style=\"width:20%;\">         </a>   <label style=\"width:15%;\" ><input type=\"submit\" value=\"Send\"></label><a style=\"width:27%;\"></a></p>";
    Page += "</form>";
    Page += "\n<p><a href=\"breath\"><button>Breathing On/Off</button></a>&nbsp;<a href=\"color\"><button>Chaning Color On/Off</button></a></p>";
    // Page += "\n<h5>Config Modes</h5>";
    // Page += "\n<form><p2>";
    // Page += "\n<b>BRIGHTNESS</b> <input name=\"LedBrs\" type=\"number\" min=\"0\" max=\"255\" step=\"1\" value=\"" + String(LedBrs) + "\"> <input type=\"submit\" value\"Send\">";
    // Page += "\n
    return Page;
}


// String html_document(){
//   String sHTML;
//   sHTML = "<!doctype html>";
//   sHTML +="<html>";
//   sHTML +="<html lang=\"de\">";
// /***************** head ****************/
//   sHTML +="<head>";
//     /****** avoid favicon requests **  ** <link rel=\"shortcut icon\" href=\"data:image/x-icon;,\" type=\"image/x-icon\"> **/
//     sHTML +="<link rel=\"icon\" href=\"data:;base64,iVBORw0KGgo=\"> ";
//     sHTML +="<meta charset=\"utf-8\"><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">";    //Anpassung an Viewport für unterschiedliche Devices
//     /***************** title ***************/
//     sHTML +="<title>LetsgoING IoT</title>";
//     sHTML +="<style>h1{display: flex; flex-flow: row wrap; justify-content: center;} </style>";
//     sHTML +="<style>h1{ color: green;}</style>";
//     sHTML +="<style>h2{display: flex; flex-flow: row wrap; justify-content: center;} </style>";
//     sHTML +="<style>h2{ color: blue;}</style>";
//     sHTML +="<style>h5{display: flex; flex-flow: row wrap; justify-content: center;} </style>";
//     sHTML +="<style>p{display: flex; flex-flow: row wrap; justify-content: center; margin-bottom: 3%;} </style>";
//     sHTML +="<style>p1{display: flex; flex-flow: row wrap; justify-content: center; margin-bottom: 0%;} </style>";
//     sHTML +="<style>p2{display: flex; flex-flow: row wrap; justify-content: center; margin-bottom: 0%;} </style>";
//   sHTML +="</head>";
// /***************** body ****************/
// sHTML+= "<body>";   //onload=\"window.setInterval(updateDiv, 15000);\"

//   sHTML+= "<h1>LetsgoING</h1>";
//   sHTML+= "<h2>Internet der Dinge</h2>";

//   sHTML+= "<p1><a style=\"width:38%;\"></a><a style=\"width:20%;color: green\">LED ein</a> <a style=\"width:15%;\" href=\"LEDON\"><button> EIN </button></a> </a><a style=\"width:27%;\"> </a></p1>";
//   sHTML+= "<p><a style=\"width:38%;\"></a><a style=\"width:20%;color: red\"  >LED aus</a> <a style=\"width:15%\"; href=\"LEDOFF\"><button>AUS</button></a><a style=\"width:27%;\"> </a></p>";

//   sHTML+= "<h5>RGB-LED PWM-Werte</h5>";
//   sHTML+= "<form><p2>";
//   sHTML+= "<a style=\"width:38%;\"></a> <a style=\"width:20%;color: red\"> Rot</a>  <a style=\"width:15%;\" ><input name=\"rot\" type=\"number\" min=\"0\" max=\"255\" step=\"1\" value=\"80\" ></a><a style=\"width:27%;\"> </a>";
//   sHTML+= "<a style=\"width:38%;\"></a> <a style=\"width:20%;color: green\">Grün</a><a style=\"width:15%;\" ><input name=\"gruen\" type=\"number\" min=\"0\" max=\"255\" step=\"1\" value=\"80\"></a><a style=\"width:27%;\"> </a>";
//   sHTML+= "<a style=\"width:38%;\"></a> <a style=\"width:20%;color: blue\">Blau</a> <a style=\"width:15%;\" ><input name=\"blau\" type=\"number\" min=\"0\" max=\"255\" step=\"1\" value=\"80\"></a><a style=\"width:27%;\"> </a>";
//   sHTML+= "</p2>";
//   sHTML+= "<p><a style=\"width:38%;\"></a> <a style=\"width:20%;\">         </a>   <label style=\"width:15%;\" ><input type=\"submit\" value=\"senden\"></label><a style=\"width:27%;\"></a></p>";
//   sHTML+= "</form>";

//   sHTML+= "<h5>analoger Schwellwert</h5>";
//   sHTML+= "<form><p2><a style=\"width:38%;\"></a> <a style=\"width:20%;\"> <input name=\"schwell\" type=\"number\" min=\"0\" max=\"1024\" step=\"10\" value=\"300\"> </a> <a style=\"width:15%;\"><input type=\"submit\" value=\"senden\"></a><a style=\"width:27%;\"> </a></p2>";
//   //sHTML+= "<p><a style=\"width:28%;\"></a> <a style=\"width:30%;\">         </a>   <label style=\"width:15%;\" ><input type=\"submit\" value=\"senden\"></label><a style=\"width:27%;\"></a></p>";
//   sHTML+= "</form>";

//   sHTML+= "<h5>PWM-Wert</h5>";
//   sHTML+= "<form><p2><a style=\"width:38%;\"></a> <a style=\"width:20%;\"> <input name=\"pwm\" type=\"number\" min=\"0\" max=\"255\" step=\"1\" value=\"0\"> </a> <a style=\"width:15%;\"><input type=\"submit\" value=\"senden\"></a><a style=\"width:27%;\"> </a></p2>";
//   sHTML+= "</form>";

//   sHTML+= "<h5>Messwerte</h5>";
//   sHTML+="<p><a style=\"width:38%;\"></a> <p3 id=\"an1\"; style=\"width:20%;\" href=\"anlg1\">#-Wert-#</p3><a style=\"width:22%;\">Analoger Pin 36   </a><a style=\"width:20%;\"></a></p>";
//   sHTML+="<p><a style=\"width:38%;\"></a> <p3 id=\"an2\"; style=\"width:20%;\">#-Wert-#</p3><a style=\"width:22%;\">Analoger Pin 39   </a><a style=\"width:20%;\"></a></p>";
//   sHTML+="<p><a style=\"width:38%;\"></a> <p3 id=\"dig\"; style=\"width:20%;\">#-Wert-#</p3><a style=\"width:22%;\">Digitaler Pin 5   </a><a style=\"width:20%;\"></a></p>";

// sHTML+= "</body>";
// sHTML+= "</html>";

// return sHTML;
// }