import processing.serial.*;

ArrayList<TEXTBOX> textboxes = new ArrayList<TEXTBOX>();
boolean send = false; // DEMO
String sender = "";
String msg = "";
Serial port; //port.write('g');

void setup() {
   size(600, 450);
   
   println(Serial.list()); 
   port = new Serial(this, Serial.list()[1], 9600); // Serial.list()[1] - this is COM8 port

   // USERNAME TEXTBOX
   // CONFIGURED USING THE GLOBAL VARS
   TEXTBOX senderTB = new TEXTBOX();
   senderTB.X = 160;
   senderTB.Y = 103;
   senderTB.W = 350;
   senderTB.H = 35;
   
   // PASSWORD TEXTBOX
   // CONFIGURED USING THE CLASS CONSTRACTOR
   TEXTBOX msgTB = new TEXTBOX(160, 153, 350, 235);
   msgTB.BorderWeight = 3;
   msgTB.BorderEnable = true;
   
   textboxes.add(senderTB);
   textboxes.add(msgTB);
}

void draw() {
   background(40, 160, 40); 
   
   // LABELS
   fill(250, 250, 250);
   text("SEND SMS", (width - textWidth("SEND SMS")) / 2, 60);
   textSize(15);
   text("Press Enter to send it", (width - textWidth("Press Enter to send it")) / 2, 80);
   textSize(24);
   text("Sender: ", 20, 130);
   text("Message: ", 20, 180);
   
   // DRAW THE TEXTBOXES
   for (TEXTBOX t : textboxes) {
      t.DRAW();
   }  
   
   // JUST FOR DEMO (DO NOT EVER DO THAT!)
   if (send && !msg.equals("")) {
      text("Message sent", (width - textWidth("Message sent")) / 2, 230);
      port.write(sender);
      port.write(msg);
      for (TEXTBOX t : textboxes) {
        t.CLEAR();
     }  
   } 
}

// ACTION HANDLERS

void mousePressed() {
   for (TEXTBOX t : textboxes) {
      t.PRESSED(mouseX, mouseY);
   }
}

void keyPressed() {
   for (TEXTBOX t : textboxes) {
      if (t.KEYPRESSED(key, (int)keyCode)) {
         send = true;
         sender = textboxes.get(0).Text; // We get the content of the first textbox
         msg = textboxes.get(1).Text; // We get the content of the second textbox
      }
   }
}
