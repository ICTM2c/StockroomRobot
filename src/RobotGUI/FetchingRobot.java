package magazijnrobot;

import arduino.*;
import java.awt.geom.Point2D;
import java.util.ArrayList;

public class FetchingRobot {

    private Arduino arduino;
    private ArrayList<Point2D.Double> route;
    private int previousX = 0;
    private int previousY = 0;

    public FetchingRobot(ArrayList<Point2D.Double> route) {
        this.route = route;
        
        setup();
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
        arduino.serialWrite("moveToStockroom");
        for (Point2D location : route) {
            int movingToX = (int) location.getX();
            int movingToY = (int) location.getY();
            boolean moving = !((previousX == movingToX) && (previousY == movingToY));

            boolean right = (movingToX > previousX);
            boolean up = (movingToY > previousY);

            if (moving) {
                if (right) {
                    arduino.serialWrite("moveRight " + (movingToX - previousX));
                } else {
                    arduino.serialWrite("moveLeft " + (previousX - movingToX));
                }
                if (up) {
                    arduino.serialWrite("moveUp " + (movingToY - previousY));
                } else {
                    arduino.serialWrite("moveDown" + (previousY - movingToY));
                }
                
                arduino.serialWrite("pickUp");
            }

            previousX = movingToX;
            previousY = movingToY;
        }
        
        arduino.serialWrite("moveDown " + previousY);
        arduino.serialWrite("moveLeft " + previousX);
        
        arduino.closeConnection();
    }
}