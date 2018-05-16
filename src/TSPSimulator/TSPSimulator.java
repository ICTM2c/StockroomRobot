package TSPSimulator;

import java.awt.Color;
import java.awt.FlowLayout;
import java.awt.TextField;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.List;
import javax.swing.JFrame;
import javax.swing.JList;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListSelectionListener;

public class TSPSimulator extends JFrame implements ActionListener, ListSelectionListener  {

    public TSPSimulator() {
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        setLayout(new FlowLayout());
        setSize(800, 500);

        pnlSimulator = new SimulatorPanel();
        add(pnlSimulator);

        _selectedCellRenderer = new SimulatorRenderer();
        liSimulators = new JList<>(new Simulator[]{new Greedy(), new SmartGreedy(), new TwoOpt(), new BruteForce(),});
        liSimulators.setSelectedIndex(0);
        liSimulators.setCellRenderer(_selectedCellRenderer);
        liSimulators.addListSelectionListener(this);

        add(liSimulators);

        tbSizeX = new TextField();
        tbSizeX.addActionListener(this);
        add(tbSizeX);

        tbSizeY = new TextField();
        tbSizeY.addActionListener(this);
        add(tbSizeY);

        List<Color> colors = pnlSimulator.setSimulators(liSimulators.getSelectedValuesList());
        _selectedCellRenderer.setColors(colors);
        setVisible(true);
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        if (e.getSource() == tbSizeX) {
            pnlSimulator.setSizeX(Integer.valueOf(tbSizeX.getText()));
        } else if (e.getSource() == tbSizeY) {
            pnlSimulator.setSizeY(Integer.valueOf(tbSizeY.getText()));
        }
    }

    @Override
    public void valueChanged(ListSelectionEvent e) {
        List<Simulator> selectedSimulators = liSimulators.getSelectedValuesList();
        List<Color> colors = pnlSimulator.setSimulators(selectedSimulators);
        _selectedCellRenderer.setColors(colors);
        liSimulators.repaint();
    }
}
