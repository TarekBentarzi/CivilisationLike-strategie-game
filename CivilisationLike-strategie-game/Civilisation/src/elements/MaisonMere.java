package elements;

import java.awt.Color;
import java.awt.Graphics2D;
import java.awt.Point;

import civilisation.Personnages;

public class MaisonMere extends TypeCase{
	private int ID_MAISON = 0; //pour savoir � qui appartient cette maison
	Personnages unite;
	private int fonds;

	public MaisonMere(int x, int y, int equipe) {
		setID_MAISON(equipe);
		setPosMaison(new Point(x,y));
		if(equipe==1) {
			setCouleurMaison(new Color(158,66,244));
		}else if(equipe==2) {
			setCouleurMaison(new Color(244,75,66));
		}
		setType("maisonM"+equipe);
		setFonds(0);
	}
	/* TODO assigner une couleur � une maison 
	 * selon un joueur dans la classe AffichageMap
	 */
	public Personnages creerUnite() {
		// cree une unite
//		return new Personnages();
		return null;
	}
	// dessine un carr� d'une certaine couleur selon l'id du joueur 
	public void dessinMaison(Graphics2D g) {
		super.dessin(getCouleurMaison(), getPosMaison(),g);
	}
	public boolean estTraversable() {
		return !super.estTraversable();
	}
	public Point getPosMaison() {
		return super.getPosition();
	}
	public void setPosMaison(Point posMaison) {
		super.setPosition(posMaison);
	}
	public Personnages getUnite() {
		return unite;
	}
	public void setUnite(Personnages unite) {
		this.unite = unite;
	}
	public int getFonds() {
		return fonds;
	}
	public void setFonds(int fonds) {
		this.fonds = fonds;
	}
	public Color getCouleurMaison() {
		return super.getCouleur();
	}
	public void setCouleurMaison(Color couleurMaison) {
		super.setCouleur(couleurMaison);
	}
	public int getID_MAISON() {
		return ID_MAISON;
	}
	public void setID_MAISON(int iD_MAISON) {
		ID_MAISON = iD_MAISON;
	}
	public String getType() {
		return super.getTypeCase();
	}
	public void setType(String type) {
		super.setTypeCase(type);
	}
	@Override
	public String toString() {
		return getType();
	}
}
