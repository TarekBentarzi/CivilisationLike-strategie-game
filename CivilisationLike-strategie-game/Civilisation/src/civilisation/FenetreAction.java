package civilisation;

import java.awt.Color;
import java.awt.Dimension;
import java.awt.Point;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.List;

import javax.swing.JButton;
import javax.swing.JOptionPane;
import javax.swing.JPanel;

import affichage.AffichageMap;
import elements.MaisonMere;

public class FenetreAction extends JPanel implements ActionListener{
	
	private List<Personnages> perso;
	private final Object lock=new Object();
	Dimension d=new Dimension(90,90);
	protected JButton [] j=new JButton[7];
    private Civilisation  game;
	
	public FenetreAction(List<Personnages>perso,Civilisation game) {
	this.game=game;
		this.perso=perso;
		for(int i=0;i<j.length;i++) {
			j[i]=new JButton();
			j[i].addActionListener(this);
			j[i].setBackground(Color.WHITE);
			j[i].setSize(d);
			j[i].setPreferredSize(d);
			this.add(j[i]);
		}
		int taille=100;
		setPreferredSize(new Dimension(100,100));
		setBackground(Color.WHITE);
		for(int i=0;i<7;i++) {
			j[i].setLocation(0,taille);
			taille=taille+100;
		}
	   
	   j[0].setText("Attaque");
	   j[1].setText("Sentinelle");
	   j[2].setText("Recolte");
	   j[3].setText("Annuler");
	   j[4].setText("Creer");
	}


	

	
	@Override
	public void actionPerformed(ActionEvent e) {
		

		if(e.getSource()==j[0]) {
			
			for(int i=0;i<perso.size();i++) {
				if(perso.get(i).getSelected()==true) {
				
					AffichageMap.compteur=0;
					
			perso.get(i).setAttaque(true);
			JOptionPane.showMessageDialog(null,"Choisissez une case pour l'attaquant ou clic droit pour annuler","deplacement",JOptionPane.INFORMATION_MESSAGE);
					//perso.get(i).setEtat(perso.get(i).getEtatAttaquant());
					
				}
			}
	    //f.listePersos.get(1).setSelected(false);
		}
		if(e.getSource()==j[1]) {
			for(int i=0;i<perso.size();i++) {
				if(perso.get(i).getSelected()==true) {
					AffichageMap.compteur=0;
					
			perso.get(i).setProtege(true);
			JOptionPane.showMessageDialog(null,"Choisissez deux cases pour la sentinelle ou clic droit pour annuler","deplacement",JOptionPane.INFORMATION_MESSAGE);
					
				}
			}
	    //f.listePersos.get(1).setSelected(false);
		}
		if(e.getSource() == j[2]) {
			for(int i=0;i<perso.size();i++) {
				if(perso.get(i).getSelected()==true) {
					AffichageMap.compteur=0;
					perso.get(i).setRecolte(true);
					JOptionPane.showMessageDialog(null,"Choisissez une pile d'or cases pour le recolteur ou clic droit pour annuler","deplacement",JOptionPane.INFORMATION_MESSAGE);

				}
			}
		}
		if(e.getSource()== j[4]) {
			if(game.getClass().getName().equals("civilisation.Civilisation")) {
					for(int i=0; i<AffichageMap.getElements().size(); i++) {
						if(AffichageMap.getElement(i).getTypeCase().equals("maisonM1")) {
							System.out.println(AffichageMap.getElement(i));
							MaisonMere m1 = (MaisonMere) AffichageMap.getElement(i);
								if(m1.getFonds()>=50) {
								m1.setFonds(m1.getFonds()-50);
								AffichageMap.getListePersos().add(new Personnages(13,"peach",new Point(314,19),1,false));
							}else {
								JOptionPane.showMessageDialog(null,"Pas assez d'or !","Message (joueur 1)",JOptionPane.INFORMATION_MESSAGE);
							}
						break;
					}
				}	
			}
			if(game.getClass().getName().equals("civilisation.Civilisation2")) {
				for(int i=0; i<AffichageMap.getElements().size(); i++) {
					MaisonMere m2;
					if(AffichageMap.getElement(i).getTypeCase().equals("maisonM2")) {
						 m2 = (MaisonMere) AffichageMap.getElement(i);
						System.out.println(AffichageMap.getElement(i));
						if(m2.getFonds()>=50) {
							m2.setFonds(m2.getFonds()-50);
							AffichageMap.getListePersos().add(new Personnages(13,"peach",new Point(314,19),1,false));
						}else{
							JOptionPane.showMessageDialog(null,"Pas assez d'or !","Message (joueur2)",JOptionPane.INFORMATION_MESSAGE);
						}
						break;
					}
				}
			}
		}
	}
}