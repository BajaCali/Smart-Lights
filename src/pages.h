
typedef enum {
    MAIN = 1,
    LED = 2
} page;

String main_page();
String LED_page();
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

String show_page(page page){
    String Page = header() + style_sheet();
    switch(page){
        case 1:
        return Page + main_page();
        break;
        case 2:
        return Page + LED_page();
        break;
    }
}

String main_page(){
    String Page;
    Page += "\n<h1>What a nice colours!</h1>";
    Page += "\n<h6>We've already added a new code</h6>";
    Page += "\n<p>Change MODE or turn Off <a href=\"counter\"><button>CHANGE</button></a>&nbsp;<a href=\"off\"><button>OFF</button></a></p>";
    // Page += "\n<p>LED #2 <a href=\"on2\"><button>ON</button></a>&nbsp;<a href=\"off2\"><button>OFF</button></a></p>";
    Page += "\n</html>";
    return Page;
}

String LED_page(){
    String Page;
    Page += "\n<h1>What a nice colours!</h1>";
}