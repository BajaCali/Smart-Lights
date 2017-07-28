
typedef enum {
    MAIN = 1,
    LEDS = 2
} page;

page current_page = MAIN;

void main_switch(char* input);
String main_page();
void LEDS_switch(char* input);
String LEDS_page();
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
    switch(page){
        case MAIN:
        main_switch(input);
        break;
        case LEDS:
        LEDS_switch(input);
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
    }
    return Page + ending();
}

void main_switch(char* input){
    if (strstr(input,"GET /LEDS") > 0){
        current_page = LEDS;
        Serial.println("Going to LED_page");
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
        cnt = 1;
        Serial.println("off");
    }
    else if(strstr(input,"GET /MAIN_page")){
        current_page = MAIN;
        Serial.println("Going to MAIN_page");
    }
}

String LEDS_page(){
    String Page;
    Page += "\n<a href=\"MAIN_page\"><button>MAIN Page</button></a>";
    Page += "\n<h3>What a nice colours!</h3>";
    Page += "\n<p>Change MODE or turn Off <a href=\"counter\"><button>CHANGE</button></a>&nbsp;<a href=\"off\"><button>OFF</button></a></p>";
    return Page;
}