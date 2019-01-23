package etats;


import java.awt.Point;
import java.util.Timer;
import java.util.TimerTask;

import affichage.AffichageMap;
import civilisation.Personnages;
import elements.MaisonMere;
import elements.PileOr;
import elements.SolVierge;
import elements.TypeCase;

public class Recolteur implements EtatPersonnage{
	private Personnages perso;
	private PileOr mine;
	private Point depot;//endroit où il pose l'or
	private int sac;//prend uniquement 10 pieces
	public Recolteur(Personnages perso) {
		this.perso=perso;
		depot = new Point();
		recolte();
	}
	//getters & setters
	public int getSac() {
		return sac;
	}

	public void setSac(int butin) {
		this.sac = butin;
	}

	//méthodes de l'interface
	@Override
	public void attaque() {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void surveille() {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void recolte() {
			Timer actionRecolte = new Timer();
			actionRecolte.schedule(new TimerTask() {
				@Override
				public void run() {
					if (perso.getEtatCourant() == perso.getEtatRecolteur()) {
					
						
						for(int i=0; i<AffichageMap.getElements().size(); i++) {
							TypeCase e = AffichageMap.getElements().get(i);
							if(e.getTypeCase()== "pile" && AffichageMap.getElements().get(i).getPosition().x==perso.getPositionDestination().x && AffichageMap.getElements().get(i).getPosition().y==perso.getPositionDestination().y) {
								System.out.println("C'est bien une pile d'or");
								mine = (PileOr) e;
							}
						}
	
					if(mine!=null) {
						//perso.setPositionDestination(new Point(mine.getPosition().x,mine.getPosition().y));
					     if(getSac()==0) {
					    
//						Point p =AffichageMap.infoClique(mine.getPosition());
				if(perso.getPositionCaseX()!=mine.getPosition().x || perso.getPositionCaseY()!=mine.getPosition().y) {
				//	System.out.println(" perso "+perso.getPosition()+" mine :"+mine.getPosition());
					//	System.out.println(getSac());
					perso.setPositionDestination(new Point(mine.getPosition().x+1,mine.getPosition().y));
			//		System.out.println(mine.getPosition().x+""+perso.getPositionCaseX());
					perso.move();	
				}else{
					System.out.println("Bien arrivé!");
				}
				//System.out.println(perso.getPosition().x+" "+mine.getPosition().x+" "+mine.getPosition().y);
					//System.out.println("Pile or (x,y)=(" +mine.getX()+","+mine.getY()+")"+getSac());
				if(perso.getPositionCaseX()==mine.getPosition().x+1 && perso.getPositionCaseY()==mine.getPosition().y) {
	
				if(mine.getQuantiteOr()>0) {
		System.out.println("sac remplis");
					setSac(10);
					mine.setQuantiteOr(mine.getQuantiteOr() - getSac());
				
					System.out.println("quantité d'or dans la mine ="+ mine.getQuantiteOr());
					System.out.println("quantité d'or dans le sac ="+ getSac());
					//perso.setPositionDestination(/*positionDestination*/);//position d'une case de la maison mère
					//perso.move();
				}else{
					
					//le mineur redevient normal
					cancel();
					perso.setEtat(perso.getEtatNormal());
					//ICI !!!!!!!!!!!
					//AffichageMap.getElements().remove(mine);
		
					mine.setTraversable(true);
					mine.setType("sol");
				/*TypeCase e =new SolVierge(mine.getPosition().x,mine.getPosition().y);
				e.estTraversable();*/
					//System.out.println(mine.getTypeCase());
					
					//mine.setTraversable(true);
		
					System.out.println("Fin de la récolte !");
					
				}
				}
				
					}else {
						if(perso.getEquipe()==1) {
						perso.setPositionDestination(new Point(2,0));
						MaisonMere m1=(MaisonMere)AffichageMap.getElements().get(0);
						perso.move();
						if(perso.getPositionCaseX()==2 && perso.getPositionCaseY()==0) {
							m1.setFonds(m1.getFonds()+getSac());
							setSac(0);
							System.out.println("arriver a la base sac ="+getSac());
							System.out.println("la");
							perso.move();
							//perso.setPositionDestination(mine.getPosition());
							
						}
					}
						else if(perso.getEquipe()==2) {
							perso.setPositionDestination(new Point(9,10));
							MaisonMere m2=(MaisonMere)AffichageMap.getElements().get(210);
							perso.move();
							if(perso.getPositionCaseX()==9 && perso.getPositionCaseY()==10) {
								m2.setFonds(m2.getFonds()+getSac());
								setSac(0);
								perso.move();
								//perso.setPositionDestination(mine.getPosition());
							}
							}
						
					}
					}else {
						perso.setEtat(perso.getEtatNormal());
						cancel();
					}
			}	
		  }	
		}, 0, 2000 );
	/*	if(perso.getPosition().equals(perso.getPositionDestination()) == false) {
			perso.setPositionDestination(new Point(0,3));
			perso.move();
		}*/
	}
	
	
	
	@Override
	public void estAttaque(int degats) {
		// TODO Auto-generated method stub
		
	}
	@Override
	public void move() {
		/*
		System.out.println("Je suis récolteur");
		System.out.println("Donnez moi la position d'une mine d'or et j'irai récolter de l'or si la mine est pleine.");
		//recherche une mine d'or*/
//		recolte();
		
//		if(p.))) {
//			perso.move();
//		}else{
//			System.out.println("Bien arrivé!");
//			System.out.println(perso.getPosition());
//		}
	}

}
