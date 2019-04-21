import processing.serial.*;

boolean hidden = false;
Serial mySerial;
PrintWriter output;

void setup() {
   mySerial = new Serial( this, Serial.list()[1], 9600 );
   output = createWriter( "chats.txt" );
}

void draw() {
    if(!hidden) {
      surface.setVisible(false); //This is what you're looking for.
      hidden = true;
    }
  
    if (mySerial.available() > 0 ) {
         String value = mySerial.readString();
         if ( value != null ) {
              if (value.equals("finish")) close_chats();
              output.println( value );
         }
    }
}

void close_chats() {
    output.flush();  // Writes the remaining data to the file
    output.close();  // Finishes the file
    exit();  // Stops the program
}
