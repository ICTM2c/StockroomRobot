package magazijnrobot;

import TSPSimulator.*;
import BPPSimulator.*;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.geom.Point2D;
import java.io.File;
import java.util.ArrayList;
import javax.swing.JFrame;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListSelectionListener;

/**
 *
 * @author jonat
 */
public class RobotGUI extends JFrame implements ActionListener, ListSelectionListener {

    private ArrayList<Point2D.Double> route;
    private ArrayList<Integer> bins;
    private TSPSimulator tspSimulator;
    private BPPSimulator bppSimulator;

    public RobotGUI() {
        
    }

    public void importOrder(File json) {

    }

    public void start() {
        FetchingRobot fetchingRobot = new FetchingRobot(route);
        PackingRobot packingRobot = new PackingRobot(bins);
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        
    }

    @Override
    public void valueChanged(ListSelectionEvent e) {
        
    }
}
