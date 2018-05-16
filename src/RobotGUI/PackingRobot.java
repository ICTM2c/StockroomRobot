package magazijnrobot;

import arduino.*;
import java.util.ArrayList;

public class PackingRobot {
    private ArrayList<Integer> bins;
    private Arduino arduino;
    
    public PackingRobot(ArrayList<Integer> bins) {
        this.bins = bins;
    }
    
    private void setup() {
        arduino = new Arduino("COM5", 9600);
        if (arduino.openConnection()) {
            loop();
        } else {
            System.out.println("Verbinding Arduino mislukt.");
        }
        
        loop();
    }
    
    private void loop() {
        for(int bin : bins) {
            arduino.serialWrite("addToBin " + bin);
        }
        
        arduino.closeConnection();
    }
}
