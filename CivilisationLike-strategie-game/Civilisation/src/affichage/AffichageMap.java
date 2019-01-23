package affichage;

import java.awt.Color;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.Image;
import java.awt.Point;
import java.awt.Rectangle;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.event.MouseMotionListener;
import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

import javax.imageio.ImageIO;
import javax.swing.JLabel;
import javax.swing.JLabel;
import javax.swing.JLabel;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;

import civilisation.Civilisation;
import civilisation.Personnages;
import elements.Arbre;
import elements.Boue;
import elements.MaisonMere;
import elements.PileOr;
import elements.SolVierge;
import elements.Teleporteur;
import elements.TypeCase;
import observer.Observateur;

public class AffichageMap extends JPanel implements Observateur, Affichage, MouseListener, MouseMotionListener {
	//le compteur
	public static int compteur;
	// nombre de colonnes
	public static final int colonnes = 20;
	// nombre de lignes
	public static final int lignes = 20;
	// taille des cases en pixels
	public static final int tailleCases = 69;
	// nombre de pixels separant chaque unitée dans une meme case du coté
	public static final int distance_unités_horizontale = tailleCases / 3;
	// nombre de pixels separant chaque unitée dans une meme case du sommet/bas de
	// la case
	public static final int distance_unités_verticale = tailleCases / 5;
	//taille de toute la carte
	private int tailleCarte;
	//nombre d'elements dans le tableau elements
//	private int nbElements;
	//liste des elements de la grille de jeu (cases)
//	private TypeCase [] elements;
	private static List <TypeCase> elements;
	// le jeu
	// images persos
	private Image[] img = new Image[200];
	private Image[] img2= new Image[200];
	private Civilisation game;
	// liste de persos a afficher
	private static List<Personnages> listePersos;
	private List<Observateur> observateurs;
	// affichage selection
	private Rectangle selection;
	private Point dessin;
	// coordonnées des points x et y du rectangle de selection
	private int selectX;
	private int selectY;
	private int destSelectX;
	private int destSelectY;
    private JLabel j1=new JLabel();

	private int getTailleCarte() {
		return tailleCarte;
	}
	private void setTailleCarte(int tailleCarte) {
		this.tailleCarte = tailleCarte;
	}
	public static int getColonnes() {
		return colonnes;
	}
	public static int getLignes() {
		return lignes;
	}
	
	public static int getTaillecases() {
		return tailleCases;
	}
//	public int getNbElements() {
//		return nbElements;
//	}
	public int getNbElements() {
		return elements.size();
	}
	public static List<Personnages> getListePersos() {
		return listePersos;
	}
	public static List<TypeCase> getElements() {
		return elements;
	}
	public static TypeCase getElement(int index) {//retourne une valeur de l'énumération(élément du jeu)
			return elements.get(index)!=null?elements.get(index):null;
	}
	private TypeCase getCase(int index) {//retourne une valeur de l'énumération(élément du jeu)
//		if(index>=getLignes()|| index>=getColonnes()) {
//			return getElement(index/getLignes());
//		}
		return getElement(index);
}
//	
//	public TypeCase getCase(int x, int y) {//retourne une valeur de l'énumération(élément du jeu)
//		return elements.get(y*getLignes()+x);
//	}
	
	public static TypeCase getCase(int x, int y) {//retourne une valeur (élément du jeu)
		for(int i=0; i<getElements().size(); i++) {
			if (getElements().get(i).getX()==x 
					&& getElements().get(i).getY()==y) {
				return getElements().get(i);
			}
		}
		return null;
	}
	//ajout d'un élement (une case) dans le tableau elements(grille du jeu)
	private void addSolVierge(TypeCase element) {
		if(elements.size()< getTailleCarte()) {
			elements.add(element);
		}
	}
	private int getIndex(int x, int y) {
		for(int i=0; i<getNbElements(); i++)
		{
			if(elements.get(i).getX()== x && elements.get(i).getY()==y)
				return i;
		}
		return -1;
	}
	private TypeCase getElement(int x, int y) {
		for(int i=0; i<getNbElements(); i++)
		{
			if(elements.get(i).getX()== x && elements.get(i).getY()==y) {
//				System.out.println("Dans getIndex()");
//				System.out.println(elements.indexOf(elements.get(i)));
//				System.out.println(getElement(i));
				return elements.get(i);
			}
		}
		return null;
	}
//	private void setElement(int x,int y,TypeCase element) {
//		elements.set(getIndex(x,y), element);
//	}
	private void addElement(String nom, int x, int y) {
		if(nom!=null) {
			switch (nom) {
			case "arbre":
				elements.set(getIndex(x,y), new Arbre(x,y));
				break;
			case "boue":
				elements.set(getIndex(x,y), new Boue(x,y));
				break;
			case "maisonM1":
				elements.set(getIndex(x,y), new MaisonMere(x,y,1));
				break;
			case "maisonM2":
				elements.set(getIndex(x,y), new MaisonMere(x,y,2));
				break;
			case "pile":
				elements.set(getIndex(x,y), new PileOr(x,y));
				break;
			case "sol":
				elements.set(getIndex(x,y), new SolVierge(x,y));
				break;
			case "teleporteur":
				elements.set(getIndex(x,y), new Teleporteur(x,y));
				break;
			}
		}
	}
	private void placementMaison(int equipe, int dim) {
		if(equipe == 1 || equipe== 2)
			for(int x=dim; x <dim+2; x++) {
				for(int y=dim; y<dim+2; y++) {				
					addElement("maisonM"+equipe,x,y);
				}
			}
	}
	/*Constructeur*/
	public AffichageMap(Civilisation game) {
		

		this.add(j1);
	
		j1.setText("Joueur1:");
		
		j1.setVisible(true);
		
		//j2.setText("eee");
		setBackground(Color.white);
		this.setFocusable(true);
		setTailleCarte(lignes * colonnes);
		//initialisation du tableau de case
		elements = new ArrayList<>();
		observateurs = new ArrayList<Observateur>();
		this.listePersos=game.getPersos();
		this.game = game;
		//les cases vierges
		for(int x=0; x <(getColonnes()); x++) {
			for(int y=0; y<(getLignes()); y++) {				
				addSolVierge(new SolVierge(x,y));
			}
		}
		addElement("arbre",0,0);
		addElement("arbre",1,1);
		addElement("arbre",2,2);
		addElement("arbre",2,3);
	    addElement("pile",2,8);
		addElement("pile",8,1);
		addElement("pile",17,12);
		addElement("pile",15,18);
		addElement("teleporteur",11,5);
		addElement("teleporteur",0,5);
		ligneBoue(4);
		placementMaison(1,0);
		placementMaison(2,10);
		//Personnages
		initImagePerso();
		setPreferredSize(new Dimension(colonnes * tailleCases, lignes * tailleCases));
		addMouseListener(this);
		addMouseMotionListener(this);
			
	}
	@Override
	public void paintComponent(Graphics g) {
		
		super.paintComponent(g);
		int compteurfin=0;
	
		
		MaisonMere M1=(MaisonMere)getElements().get(0);
		MaisonMere M2=(MaisonMere)getElements().get(210);
		j1.setText("Joueur1: "+M1.getFonds()+" Joueur2: "+M2.getFonds());
		
		for(int i=0;i<getElements().size();i++) {
			if(getElements().get(i).getTypeCase()=="pile") {
				compteurfin++;
			}
		}
		if(compteurfin==0) {
			if(M1.getFonds()>M2.getFonds()) {
			JOptionPane.showMessageDialog(null,"fin du jeu le joueur 1 gagne","fin",JOptionPane.INFORMATION_MESSAGE);
			return;
			}else if(M2.getFonds()>M1.getFonds()) {
					JOptionPane.showMessageDialog(null,"fin du jeu le joueur 2 gagne","fin",JOptionPane.INFORMATION_MESSAGE);
					return;
					}else {	
						JOptionPane.showMessageDialog(null,"egalité","fin",JOptionPane.INFORMATION_MESSAGE);
						return;	
				}
		}
		Graphics2D g2d=(Graphics2D)g;
		// Graphics2D g2 = (Graphics2D) g;
		/*
		 * g2.setColor(Color.WHITE); g2.fillRect(vueX, vueY, 490, 490);
		 */
		//le rectangle rouge de sélection si une unité est sélectionnée
		dessinRectangleSelectionPerso(g2d);
		dessinImagePerso(g2d);//les images des personnages sur la carte
		dessinGrille(g2d);//La grille du jeu
		dessinCases(g2d);//Les cases de la grille
		
	}
	//initialisation des images de perso
	void initImagePerso() {
		try {
			
			img[0] = ImageIO.read(new File("perso.gif"));
			img[1]=ImageIO.read(new File("perso2.gif"));
			for (int j = 0; j < listePersos.size(); j++) {
				// initialisation des images
			
			
				
			
				//img2[j]=new ImageIcon(this.getClass()
		               // .getResource("C:\\Users\\admin\\eclipse-workspace\\Civilisation\\perso.gif"));
				// ajouter cet observateur pour (tous les observables personnages)
				listePersos.get(j).ajouterObservateur(this);
			}
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
	private void ligneBoue(int x) {
		for(int i=x; i<2*x; i++) {
			addElement("boue",i,x);
		}
	}
	//Crée et dessine le rectangle rouge de sélection si une unité est sélectionnée
	void dessinRectangleSelectionPerso(Graphics g) {
		//Création du dessin du rectangle de sélection
		if (selection != null) {
			Graphics2D g2d = (Graphics2D) g;
			g2d.setColor(Color.RED);
			g2d.draw(selection);
			
			for (int i = 0; i < listePersos.size(); i++) {
				if (selectY < listePersos.get(i).getPosition().y
						&& listePersos.get(i).getPosition().y < destSelectY + selectY
						&& selectX < listePersos.get(i).getPosition().x
						&& listePersos.get(i).getPosition().x < destSelectX + selectX) {
					// count = count + 1;
					if(game.getClass().getName().equals("civilisation.Civilisation") && listePersos.get(i).getEquipe()==1) {
						listePersos.get(i).setSelected(true);
					}else if(game.getClass().getName().equals("civilisation.Civilisation2") && listePersos.get(i).getEquipe()==2){
						listePersos.get(i).setSelected(true);
					}
				}
			}
		}
		//dessin du rectangle autour de l'unité sélectionnée
		for (int i = 0; i < listePersos.size(); i++) {
			if (listePersos.get(i).getSelected() == true) {
				g.setColor(Color.RED);
				g.drawRect(listePersos.get(i).getPosition().x, listePersos.get(i).getPosition().y, 50, 50);
			}
		}
	}
	//dessine les images des personnages sur la carte
	void dessinImagePerso(Graphics g) {

		for (int i = 0; i < listePersos.size(); i++) {
			if(listePersos.get(i).getEquipe()==1) {
			//	p1.add(listePersos.get(i));
				//g.setColor(Color.BLACK);
				//g.fillOval(listePersos.get(i).getPosition().x, listePersos.get(i).getPosition().y, 20, 20);
				g.drawImage(img[0], listePersos.get(i).getPosition().x, listePersos.get(i).getPosition().y, null);

			}
			if(listePersos.get(i).getEquipe()==2) {
				//	p1.add(listePersos.get(i));
				//g.setColor(Color.RED);
					//g.fillOval(listePersos.get(i).getPosition().x, listePersos.get(i).getPosition().y, 20, 20);
					g.drawImage(img[1], listePersos.get(i).getPosition().x, listePersos.get(i).getPosition().y, null);

				}
			
			//g.drawImage(img[i], listePersos.get(i).getPosition().x, listePersos.get(i).getPosition().y, null);
	
           // img2[i].paintIcon(this,g,listePersos.get(i).getPosition().x,listePersos.get(i).getPosition().y);
		}
	/*	for (int i = 0; i < p1.size(); i++) {
		
		System.out.println("la"+p1.get(i).getEquipe()+" "+i);	
		}*/
		
		
	}
	//dessine les cases dans la grille
	void dessinCases(Graphics2D g2d) {
		for(int i=0; i<getNbElements(); i++) {
			TypeCase e=getElement(i);
			if(e!=null) {
				if(e.getX()*getColonnes() < getTailleCarte() && e.getY()*getLignes()< getTailleCarte())
					drawTile(e.getX()*getTaillecases(), e.getY()*getTaillecases(),e.getTypeCase(),g2d);
			}
		}
	}
	
	//dessine la grille du jeu
	void dessinGrille(Graphics g) {
		g.setColor(Color.DARK_GRAY);
		g.drawRect(0, 0, getWidth() - 1, getHeight() - 1);
		for (int x = 0; x < colonnes; x++) {
			for (int y = 0; y < lignes; y++) {
				g.drawLine(x * tailleCases, 0, x * tailleCases, getHeight());
				g.drawLine(0, y * tailleCases, getWidth(), y * tailleCases);
			}
		}
	}
	//dessine un element selon son type
	private void drawTile(int x, int y, String type, Graphics2D g) {
		//chaque element correspond a une case
	if(type!=null)
		switch (type) {
			case "arbre":
				Arbre arbre = new Arbre(x,y);
				arbre.dessin(g);
				break;
			case "boue":
				TypeCase boue = new Boue(x,y);
				boue.dessin(g);
				break;
			case "maisonM1":
				TypeCase maisonMere = new MaisonMere(x,y,1);
				maisonMere.dessin(g);
				break;
			case "maisonM2":
				TypeCase maisonMere2 = new MaisonMere(x,y,2);
				maisonMere2.dessin(g);
				break;
			case "pile":
				TypeCase pileOr = new PileOr(x,y);
				pileOr.dessin(g);
				break;
			case "sol":
				SolVierge solVierge = new SolVierge(x,y);
				solVierge.dessinSolVierge(g);
				break;
			case "teleporteur":
				Teleporteur teleporteur = new Teleporteur(new Point(x,y));
				teleporteur.dessinTeleporteur(g);
				break;
		}
	}
	//Fonctions liés aux évenements de la souris
	public void mousePressed(MouseEvent e) {
		// Position du point de la souris
		dessin = e.getPoint();
		// Rectangle
		selection = new Rectangle(dessin);
	}

	@Override
	public void mouseReleased(MouseEvent e) {

		selection = null;
		repaint();
	}

	public void mouseEntered(MouseEvent e) {

	}

	@Override
	public void mouseDragged(MouseEvent e) {
		// minimum entre dessin.x ou y et poistion du clic a la coordonnée x ou y
		selectX = (int) Math.min(dessin.x, e.getX());
		selectY = (int) Math.min(dessin.y, e.getY());
		destSelectX = (int) Math.abs(e.getX() - dessin.x);
		destSelectY = (int) Math.abs(e.getY() - dessin.y);
		selection.setBounds(selectX, selectY, destSelectX, destSelectY);

		repaint();
	}
	private void infoClique(Point p) {
		System.out.println("Position du clic(en pixels) x="+ p.x+",y="+p.y);
		System.out.println("Position du clic  x="+ (p.x/getTaillecases())+",y="+(p.y/getTaillecases()));
	}
	@Override
	public void mouseClicked(MouseEvent e) {
		
	
//System.out.println(e.getPoint().x/tailleCases+" "+e.getPoint().y/tailleCases);
		// setPosCaseDestX(e.getX());
		// System.out.println(getPosCaseDestX());
		// Clic gauche de la souris
		if (e.getButton() == MouseEvent.BUTTON1) {
			compteur++;
			
			//System.out.println(compteur);
			// if (count != 0) {
			infoClique(e.getPoint());
			//DES AJOUTS ICI
			for (int i = 0; i < listePersos.size(); i++) {
				// marche();
				if (listePersos.get(i).getSelected() == true) {
					listePersos.get(i).setPositionDestination(new Point(e.getX() / 70, e.getY() / 70));
					listePersos.get(i).seDeplace();
					actualiser();
				}
			}
			
		}
		// }

		// Récupération de la position
		Point position = e.getPoint();

		// clic de la souris droit
		if (e.getButton() == MouseEvent.BUTTON3) {

			for (int i = 0; i < listePersos.size(); i++) {
				listePersos.get(i).setSelected(false);
				if(listePersos.get(i).getAttaque()==true || listePersos.get(i).isProtege()==true) {
				listePersos.get(i).setAttaque(false);
				listePersos.get(i).setRecolte(false);
				listePersos.get(i).setProtege(false);
				JOptionPane.showMessageDialog(null,"Action annulée","deplacement",JOptionPane.INFORMATION_MESSAGE);

				}
			}

		}

	}

	@Override
	public void mouseExited(MouseEvent arg0) {
		// TODO Auto-generated method stub

	}

	@Override
	public void mouseMoved(MouseEvent arg0) {
		// TODO Auto-generated method stub

	}

	@Override
	public void actualiser() {

		repaint();

	}
	@Override
	public void actualiseInfo(int fonds) {
		
		
	}

}
