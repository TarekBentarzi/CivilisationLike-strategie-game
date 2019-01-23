package elements;

import java.awt.Color;
import java.awt.Graphics2D;
import java.awt.Point;
import java.util.Timer;
import java.util.TimerTask;

import javax.net.ssl.SSLException;

import affichage.AffichageMap;
import civilisation.Personnages;
import observer.Observateur;

public class Boue extends TypeCase {
	private Personnages unite;
	int timeout;
	public Boue(int x,int y) {
		setType("boue");
		setPosBoue(new Point(x,y));
		setCouleurBoue(new Color(139,69,19)); //couleur marron
	}
	//dessine un carr� marron de 70*70
	public void dessinBoue(Graphics2D g) {
		super.dessin(getCouleurBoue(), getPosBoue(), g);
	}
	public Point getPosBoue() {
		return super.getPosition();
	}
	public void setPosBoue(Point posBoue) {
		super.setPosition(posBoue);
	}
	public Color getCouleurBoue() {
		return super.getCouleur();
	}
	public void setCouleurBoue(Color couleurBoue) {
		super.setCouleur(couleurBoue);
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
	public Personnages getUnite() {
		return unite;
	}
	public void setUnite(Personnages unite) {
		this.unite = unite;
	}
	public void ralentir(TimerTask timerTask) {
		synchronized(timerTask) {
			try {
				timerTask.wait(1000);
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}

	}
}
