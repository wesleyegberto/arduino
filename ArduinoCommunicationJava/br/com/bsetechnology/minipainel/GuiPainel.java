/**
 * @author Wesley Egberto de Brito
 * @date 11/01/2014
 * 
 * User interface to control the Arduino's components
 */
package br.com.bsetechnology.minipainel;

import java.awt.Font;
import java.awt.SystemColor;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.io.FileNotFoundException;
import java.io.IOException;

import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JTextField;
import javax.swing.UIManager;
import javax.swing.border.EtchedBorder;
import java.awt.Toolkit;

public class GuiPainel extends JFrame {
	private static final long serialVersionUID = -7889774028840478695L;

	ArduinoComm arduinoComm;
	private JLabel lblTitulo;
	private JPanel ledPanel;
	private JPanel sensorPanel;
	private JButton btnGreenLed;
	private JLabel lblStatusGreenLed;
	private JButton btnYellowLed;
	private JLabel lblStatusYellowLed;
	private JButton btnRedLed;
	private JLabel lblStatusRedLed;
	private JPanel configPanel;
	private JButton btnConect;
	private JLabel lblSerialPort;
	private JTextField txtSerialPort;
	private JLabel lblLuminosity;
	private JButton btnLuminosity;
	private JLabel lblLuminosityValue;
	
	private boolean isConnected;
	
	private boolean isGreenLedOn = false;
	private boolean isYellowLedOn = false;
	private boolean isRedLedOn = false;
	
	private ImageIcon GREENLED_OFF = new ImageIcon("resources/greenled_off.png");
	private ImageIcon GREENLED_ON = new ImageIcon("resources/greenled_on.png");
	private ImageIcon YELLOWLED_OFF = new ImageIcon("resources/yellowled_off.png");
	private ImageIcon YELLOWLED_ON = new ImageIcon("resources/yellowled_on.png");
	private ImageIcon REDLED_OFF = new ImageIcon("resources/redled_off.png");
	private ImageIcon REDLED_ON = new ImageIcon("resources/redled_on.png");
		
	public GuiPainel() {
		initComponents();
		lockComponents();
	}

	private void initComponents() {
		// setIconImage(Toolkit.getDefaultToolkit().getImage(""));
		try {
			UIManager.setLookAndFeel("javax.swing.plaf.nimbus.NimbusLookAndFeel");
		} catch(Exception e) {
		}

		addWindowListener(new WindowAdapter() {
			@Override
			public void windowClosed(WindowEvent e) {

			}

			@Override
			public void windowClosing(WindowEvent e) {
				if(JOptionPane.showConfirmDialog(GuiPainel.this, "Deseja fechar o painel?", "Pergunta",
						JOptionPane.YES_NO_OPTION) == JOptionPane.YES_OPTION) {
					if(arduinoComm != null)
						arduinoComm.close();
					dispose();
					System.exit(0);
				}
			}
		});
		setIconImage(Toolkit.getDefaultToolkit().getImage("resources/arduino.jpg"));
		setBackground(SystemColor.control);
		getContentPane().setLayout(null);
		setSize(600, 500);
		setResizable(false);

		lblTitulo = new JLabel("MiniPainel do Arduino");
		lblTitulo.setFont(new Font("DejaVu Sans", Font.BOLD, 26));
		lblTitulo.setBounds(132, 6, 334, 44);
		getContentPane().add(lblTitulo);
		
		configPanel = new JPanel();
		configPanel.setBounds(33, 66, 532, 48);
		getContentPane().add(configPanel);
		configPanel.setBorder(new EtchedBorder(EtchedBorder.LOWERED, null, null));
		configPanel.setLayout(null);
		
		lblSerialPort = new JLabel("Porta Serial:");
		lblSerialPort.setBounds(18, 19, 77, 15);
		configPanel.add(lblSerialPort);
		
		txtSerialPort = new JTextField();
		txtSerialPort.setBounds(107, 13, 176, 27);
		txtSerialPort.setText("/dev/ttyACM0");
		configPanel.add(txtSerialPort);
		txtSerialPort.setColumns(10);
		
		btnConect = new JButton("Conectar");
		btnConect.setBounds(295, 13, 120, 27);
		btnConect.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				if(!isConnected)
					connect();
				else
					desconnect();
			}
		});
		configPanel.add(btnConect);

		ledPanel = new JPanel();
		ledPanel.setBorder(new EtchedBorder(EtchedBorder.LOWERED, null, null));
		ledPanel.setBounds(34, 126, 259, 166);
		getContentPane().add(ledPanel);
		ledPanel.setLayout(null);

		btnGreenLed = new JButton("Acender LED Verde");
		btnGreenLed.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				boolean sucess = false;
				if(isGreenLedOn) {
					sucess = sendCommand("GL");
				} else {
					sucess = sendCommand("GH");
				}
				if(sucess) {
					isGreenLedOn = !isGreenLedOn;
					if(isGreenLedOn) {
						lblStatusGreenLed.setIcon(GREENLED_ON);
						btnGreenLed.setText("Apagar LED Verde");
					} else {
						lblStatusGreenLed.setIcon(GREENLED_OFF);
						btnGreenLed.setText("Acender LED Verde");
					}
				}
			}
		});
		btnGreenLed.setBounds(2, 2, 170, 54);
		ledPanel.add(btnGreenLed);

		lblStatusGreenLed = new JLabel("");
		lblStatusGreenLed.setIcon(GREENLED_OFF);
		lblStatusGreenLed.setBounds(194, 2, 50, 54);
		ledPanel.add(lblStatusGreenLed);

		btnYellowLed = new JButton("Acender LED Amarelo");
		btnYellowLed.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				boolean sucess = false;
				if(isYellowLedOn) {
					sucess = sendCommand("YL");
				} else {
					sucess = sendCommand("YH");
				}
				if(sucess) {
					isYellowLedOn = !isYellowLedOn;
					if(isYellowLedOn) {
						lblStatusYellowLed.setIcon(YELLOWLED_ON);
						btnYellowLed.setText("Apagar LED Amarelo");
					} else {
						lblStatusYellowLed.setIcon(YELLOWLED_OFF);
						btnYellowLed.setText("Acender LED Amarelo");
					}
				}
			}
		});
		btnYellowLed.setBounds(2, 56, 170, 54);
		ledPanel.add(btnYellowLed);

		lblStatusYellowLed = new JLabel("");
		lblStatusYellowLed.setIcon(YELLOWLED_OFF);
		lblStatusYellowLed.setBounds(194, 56, 50, 54);
		ledPanel.add(lblStatusYellowLed);

		btnRedLed = new JButton("Acender LED Vermelho");
		btnRedLed.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				boolean sucess = false;
				if(isRedLedOn) {
					sucess = sendCommand("RL");
				} else {
					sucess = sendCommand("RH");
				}
				if(sucess) {
					isRedLedOn = !isRedLedOn;
					if(isRedLedOn) {
						lblStatusRedLed.setIcon(REDLED_ON);
						btnRedLed.setText("Apagar LED Vermelho");
					} else {
						lblStatusRedLed.setIcon(REDLED_OFF);
						btnRedLed.setText("Acender LED Vermelho");
					}
				}
			}
		});
		btnRedLed.setBounds(2, 110, 170, 54);
		ledPanel.add(btnRedLed);

		lblStatusRedLed = new JLabel("");
		lblStatusRedLed.setIcon(REDLED_OFF);
		lblStatusRedLed.setBounds(194, 110, 50, 54);
		ledPanel.add(lblStatusRedLed);

		sensorPanel = new JPanel();
		sensorPanel.setBounds(305, 126, 259, 166);
		sensorPanel.setBorder(new EtchedBorder(EtchedBorder.LOWERED, null, null));
		getContentPane().add(sensorPanel);
		sensorPanel.setLayout(null);
		
		lblLuminosity = new JLabel("Luminosidade:");
		lblLuminosity.setBounds(16, 17, 97, 15);
		sensorPanel.add(lblLuminosity);
		
		lblLuminosityValue = new JLabel("Não lido.");
		lblLuminosityValue.setBounds(110, 15, 97, 17);
		sensorPanel.add(lblLuminosityValue);
		
		btnLuminosity = new JButton("");
		btnLuminosity.setIcon(new ImageIcon("resources/atualizar.png"));
		btnLuminosity.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent evt) {
				if(sendCommand("L")) {
					try {
						String value = arduinoComm.readData();
						lblLuminosityValue.setText(value);
					} catch(IOException e) {
						JOptionPane.showMessageDialog(GuiPainel.this, "Erro ao ler luminosidade: \n" + e.getMessage(), "Erro", JOptionPane.ERROR_MESSAGE);
						e.printStackTrace();
					}
					
				}
			}
		});
		btnLuminosity.setBounds(209, 8, 44, 32);
		sensorPanel.add(btnLuminosity);

		setVisible(true);
	}
	
	/**
	 * Try to connect to Arduino through serial port.
	 */
	private void connect() {
		try {
			if(txtSerialPort.getText().length() > 0)
				arduinoComm = new ArduinoComm(txtSerialPort.getText());
			else
				arduinoComm = new ArduinoComm();
				
			txtSerialPort.setEditable(false);
			isConnected = true;
			btnConect.setText("Desconectar");
			unlockComponents();
		} catch(FileNotFoundException ex) {
			ex.printStackTrace();
			lockComponents();
			JOptionPane.showMessageDialog(this, "Porta de comunicação não encontrada.", "Erro", JOptionPane.ERROR_MESSAGE);
		} catch(IOException e) {
			e.printStackTrace();
			lockComponents();
			JOptionPane.showMessageDialog(this, "Erro ao conectar ao arduino: " + e.getMessage(), "Erro", JOptionPane.ERROR_MESSAGE);
		}
	}
	
	private void desconnect() {
		lockComponents();
		arduinoComm.close();
		txtSerialPort.setEditable(true);
		isConnected = false;
		btnConect.setText("Conectar");
	}

	public void lockComponents() {
		btnGreenLed.setEnabled(false);
		btnYellowLed.setEnabled(false);
		btnRedLed.setEnabled(false);
		btnLuminosity.setEnabled(false);
	}
	
	public void unlockComponents() {
		btnGreenLed.setEnabled(true);
		btnYellowLed.setEnabled(true);
		btnRedLed.setEnabled(true);
		btnLuminosity.setEnabled(true);
	}
	
	public boolean sendCommand(String command) {
		try {
			arduinoComm.sendData(command);
			return true;			
		} catch(IOException e) {
			JOptionPane.showMessageDialog(this, "Erro ao enviar comando para o arduino: \n" + e.getMessage(), "Erro", JOptionPane.ERROR_MESSAGE);
			e.printStackTrace();
		}
		return false;
	}
}
