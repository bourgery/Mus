#include "jeu.h"
#include "jeu_IA.h"

bool choix_mus_IA(Joueur j, int carte_jetee) {
	int point_jeu = compte_jeu(&j);
	if ((carte_jetee == 0 && point_jeu >= 31) ||
	    point_jeu == 31 ||
	    point_jeu == 30 ||
	    double_pair(j) ||
	    brelan(j) ||
	    (j.main[0].valeur == ROI && j.main[1].valeur == ROI) ||
	    (j.main[0].valeur == ROI && j.main[1].valeur == VALET) ||
	    (j.main[0].valeur == ROI && j.main[1].valeur == DIX) ||
	    proba_gagner_grand(j) >= 0.95)
		return false;
	else
		return true;
}

void choix_carte_mus_IA(Joueur j, bool tab[]) {
	for (int i = 0; i < 4; i++) {
		if (j.main[i].valeur == ROI ||
		    j.main[i].valeur == VALET ||
		    j.main[i].valeur == DIX ||
		    j.main[i].valeur == AS)
			tab[i] = false;
		else
			tab[i] = true;
	}
}

void calcul_nb_main_faux_feu(float tab[]) {
	int a, b, c, d;
	for (int i = 0; i <= 30; i ++)
		tab[i] = 0.;
	for (int i = 1; i <= 40; i++) {
		for (int j = 1; j <= 40 && j != i; j++) {
			for (int k = 1; k <= 40 && k != j && k != i; k++) {
				for (int l = 1; l <= 40 && l != k && l != j && l != i; l++) {
					a = i % 10;
					b = j % 10;
					c = k % 10;
					d = l % 10;
					if (a == 0 || a >= 8)
						a = 10;
					if (b == 0 || b >= 8)
						b = 10;
					if (c == 0 || c >= 8)
						c = 10;
					if (d == 0 || d >= 8)
						d = 10;
					if (a + b + c + d <= 30)
						tab[a + b + c + d] ++;
				}
			}
		}
	}
}

float puissance(float p, int n) {
	float r = 1;
	for (int i = 0; i < n; i ++)
		r *= p;
	return r;
}

float proba_carte_superieur(Carte c) {
	float p = (10. - c.valeur) / 10;
	return p;
}

float proba_gagner_grand(Joueur j) {
	float p = 0;
	p = proba_carte_superieur(j.main[0]) + 0.1 *
	    (proba_carte_superieur(j.main[1]) + 0.1 *
	     (proba_carte_superieur(j.main[2]) + 0.1 *
	      (proba_carte_superieur(j.main[3]) + 0.1))) ;
	return (1 - p) * (1 - p) * (1 - p);
}

float proba_gagner_petit(Joueur j) {
	float p = 0;
	p = proba_carte_superieur(j.main[3]) + 0.1 *
	    (proba_carte_superieur(j.main[2]) + 0.1 *
	     (proba_carte_superieur(j.main[1]) + 0.1 *
	      (proba_carte_superieur(j.main[0]) + 0.1))) ;
	return p * p * p;
}

float proba_gagner_pair(Partie *partie, Joueur j) {
	float nb_mains = 37630.;
	float nb_mains_2_paires = 1630.;
	float nb_mains_brelan = 1440.;
	float p = 0, p_esku = 0;
	bool tab_joueur[4];
	int esku = partie->nb_tours % 4;
	tab_pair(partie, tab_joueur);
	if (double_pair(j)) {
		p += 163. * (10 - j.main[0].valeur) + 163. * (11 - j.main[2].valeur);
		p_esku += 163. * (10 - j.main[0].valeur) + 163. * (10 - j.main[2].valeur);
		p /= nb_mains;
		p_esku /= nb_mains;
	}
	else if (brelan(j)) {
		p += 144. * (11 - j.main[1].valeur);
		p_esku += 144. * (10 - j.main[1].valeur);
		p += nb_mains_2_paires;
		p_esku += nb_mains_2_paires;
		p /= nb_mains;
		p_esku /= nb_mains;
	}
	else {
		int ind_pair = pair(j);
		p += 3456. * (11 - j.main[ind_pair].valeur);//Proba d'avoir une paire de x fois le nombre de pair au dessus
		p_esku += 3456. * (10 - j.main[ind_pair].valeur);
		p += nb_mains_2_paires;
		p_esku += nb_mains_2_paires;
		p += nb_mains_brelan;
		p_esku += nb_mains_brelan;
		p /= nb_mains;
		p_esku /= nb_mains;
	}
	int nb_joueur = tab_joueur[0] + tab_joueur[1] + tab_joueur[2] + tab_joueur[3] - 1;
	if (esku == j.num_joueur ||
	    (j.num_joueur == 0 && tab_joueur[3] == false && esku == 3) ||
	    (esku == j.num_joueur - 1 && tab_joueur[j.num_joueur - 1] == false) ||
	    (j.num_joueur == 0 && tab_joueur[3] == false && tab_joueur[2] == false && esku == 2) ||
	    (j.num_joueur == 1 && tab_joueur[0] == false && tab_joueur[3] == false && esku == 3) ||
	    (esku == j.num_joueur - 2 && tab_joueur[j.num_joueur - 1] == false && tab_joueur[j.num_joueur - 2] == false)) //Si le joueur est en position esku ou comme si
		return puissance(1 - p_esku, nb_joueur);
	else
		return (1 - p) * puissance(1 - p_esku, nb_joueur - 1);
}

float proba_gagner_jeu(Partie *partie, Joueur j) {
	int points[8] = {31, 32, 40, 37, 36, 35, 34, 33};
	float nb_mains[8] = {3040., 2332., 495., 880., 880., 880., 1276., 1936.};
	float nb_mains_jeu = 11719.;
	bool tab_joueur[4];
	tab_jeu(partie, tab_joueur);
	int nb_point = compte_jeu(&j);
	int indice = indice_tableau(points, nb_point, 8);
	float p = 0, p_esku = 0;
	int esku = partie->nb_tours % 4;
	for (int i = indice; i > 0; i--)
		p_esku += nb_mains[i];
	for (int i = indice; i >= 0; i--)
		p += nb_mains[i];
	int nb_joueur = tab_joueur[0] + tab_joueur[1] + tab_joueur[2] + tab_joueur[3] - 1;
	if (esku == j.num_joueur ||
	    (j.num_joueur == 0 && tab_joueur[3] == false && esku == 3) ||
	    (esku == j.num_joueur - 1 && tab_joueur[j.num_joueur - 1] == false) ||
	    (j.num_joueur == 0 && tab_joueur[3] == false && tab_joueur[2] == false && esku == 2) ||
	    (j.num_joueur == 1 && tab_joueur[0] == false && tab_joueur[3] == false && esku == 3) ||
	    (esku == j.num_joueur - 2 && tab_joueur[j.num_joueur - 1] == false && tab_joueur[j.num_joueur - 2] == false))
		return puissance(1 - (p_esku  / nb_mains_jeu), nb_joueur);
	else
		return (1 - (p / nb_mains_jeu)) * puissance(1 - (p_esku / nb_mains_jeu), nb_joueur - 1);
}

float proba_gagner_faux_jeu(Partie *partie, Joueur j) {
	float nb_mains[31];
	float nb_mains_jeu = 79671.;
	calcul_nb_main_faux_feu(nb_mains);
	int nb_point = compte_jeu(&j);
	int esku = partie->nb_tours % 4;
	float p = 0, p_esku = 0;
	for (int i = nb_point; i < 30; i++)
		p_esku += nb_mains[i];
	for (int i = nb_point; i <= 30; i++)
		p += nb_mains[i];
	if (esku == j.num_joueur)
		return puissance(1 - (p_esku / nb_mains_jeu), 3);
	else
		return (1 - (p / nb_mains_jeu)) * puissance(1 - (p_esku  / nb_mains_jeu),  2);
}

int phase_mise_IA_grand(Partie *partie, Joueur j, int mise_precedente, int mise_totale, int mise_en_jeu) {
	int equipe = j.num_joueur % 2;
	float proba = proba_gagner_grand(j);
	switch (mise_precedente) {
	case 0: //Paso avant
		if (partie->score[(equipe + 1) % 2] + mise_en_jeu >= 40 || partie->score[(equipe + 1) % 2] == 39)
			return -1;
		if ((partie->score[equipe] + 15 <= partie->score[(equipe + 1) % 2] && partie->score[(equipe + 1) % 2] >= 25) ||
		    (partie->score[equipe] + 10 <= partie->score[(equipe + 1) % 2] && partie->score[(equipe + 1) % 2] >= 30) )
			return -1;
		if (proba >= 0.91 && partie->score[(equipe + 1) % 2] == 39)
			return -1;
		if (proba >= 0.91)
			return 2;
		else
			return 0;
		break;
	case 1://Tira
		if (proba >= 0.91)
			return -3;
		else
			return 1;
		break;
	case -1://Hordago
		if (partie->score[(equipe + 1) % 2] + mise_en_jeu >= 40 || partie->score[(equipe + 1) % 2] == 39)
			return -2;
		if (proba >= 0.97)
			return -2;
		else
			return 1;
		break;
	case -3: //Iduki
		if (mise_totale == 2 && proba >= 0.97)
			return 2;
		if (mise_totale == 2 && proba < 0.97)
			return -3;
		if (mise_totale >= 2) {
			if (proba >= 0.98)
				return 2;
			else
				return -3;
		}
		break;
	default://Mise
		if (partie->score[(equipe + 1) % 2] + mise_en_jeu >= 40 || partie->score[(equipe + 1) % 2] == 39)
			return -1;
		if ((partie->score[equipe] + 15 <= partie->score[(equipe + 1) % 2] && partie->score[(equipe + 1) % 2] >= 25) ||
		    (partie->score[equipe] + 10 <= partie->score[(equipe + 1) % 2] && partie->score[(equipe + 1) % 2] >= 30) )
			return -1;
		if (mise_totale == 2 && proba >= 0.97)
			return 2;
		if (mise_totale == 2 && proba >= 0.91)
			return -3;
		if (mise_totale == 2 && proba < 0.91)
			return 1;
		if (mise_totale >= 2 && mise_totale <= 6) {
			if (proba >= 0.97)
				return 2;
			else if (proba >= 0.95)
				return -3;
			else
				return 1;
		}
		if(mise_totale >= 6){
			if (proba >= 0.97)
				return -1;
			else if (proba >= 0.95)
				return -3;
			else
				return 1;
		}
		break;
	}
	return 0;
}

int phase_mise_IA_petit(Partie *partie, Joueur j, int mise_precedente, int mise_totale, int mise_en_jeu) {
	float proba = proba_gagner_petit(j);
	int equipe = j.num_joueur % 2;
	switch (mise_precedente) {
	case 0: //Paso avant
		if (partie->score[(equipe + 1) % 2] + mise_en_jeu >= 40 || partie->score[(equipe + 1) % 2] == 39)
			return -1;
		if ((partie->score[equipe] + 15 <= partie->score[(equipe + 1) % 2] && partie->score[(equipe + 1) % 2] >= 25) ||
		    (partie->score[equipe] + 10 <= partie->score[(equipe + 1) % 2] && partie->score[(equipe + 1) % 2] >= 30) )
			return -1;
		if (proba >= 0.91 && partie->score[(equipe + 1) % 2] == 39)
			return -1;
		if (proba >= 0.91)
			return 2;
		else
			return 0;
		break;
	case 1://Tira
		if (proba >= 0.91)
			return -3;
		else
			return 1;
		break;
	case -1://Hordago
		if (partie->score[(equipe + 1) % 2] + mise_en_jeu >= 40 || partie->score[(equipe + 1) % 2] == 39)
			return -2;
		if (proba >= 0.97)
			return -2;
		else
			return 1;
		break;
	case -3: //Iduki
		if (mise_totale == 2 && proba >= 0.97)
			return 2;
		if (mise_totale == 2 && proba < 0.97)
			return -3;
		if (mise_totale >= 2) {
			if (proba >= 0.98)
				return 2;
			else
				return -3;
		}
		break;
	default://Mise
		if (partie->score[(equipe + 1) % 2] + mise_en_jeu >= 40 || partie->score[(equipe + 1) % 2] == 39)
			return -1;
		if ((partie->score[equipe] + 15 <= partie->score[(equipe + 1) % 2] && partie->score[(equipe + 1) % 2] >= 25) ||
		    (partie->score[equipe] + 10 <= partie->score[(equipe + 1) % 2] && partie->score[(equipe + 1) % 2] >= 30) )
			return -1;
		if (mise_totale == 2 && proba >= 0.97)
			return 2;
		if (mise_totale == 2 && proba >= 0.91)
			return -3;
		if (mise_totale == 2 && proba < 0.91)
			return 1;
		if (mise_totale >= 2) {
			if (proba >= 0.98)
				return 2;
			else if (proba >= 0.95)
				return -3;
			else
				return 1;
		}
		break;
	}
	return 0;
}

int phase_mise_IA_pair(Partie *partie, Joueur j, int mise_precedente, int mise_totale, int mise_en_jeu) {
	float proba = proba_gagner_pair(partie, j);
	int equipe = j.num_joueur % 2;
	switch (mise_precedente) {
	case 0: //Paso avant
		if (partie->score[(equipe + 1) % 2] + mise_en_jeu >= 40 || partie->score[(equipe + 1) % 2] == 39)
			return -1;
		if (proba >= 0.68 && partie->score[(equipe + 1) % 2] == 39)
			return -1;
		if (proba >= 0.68)
			return 2;
		else
			return 0;
		break;
	case 1://Tira
		if (mise_totale == 2 && proba >= 0.87)
			return 2;
		if (proba >= 0.75)
			return -3;
		else
			return 1;
		break;
	case -1://Hordago
		if (partie->score[(equipe + 1) % 2] + mise_en_jeu >= 40 || partie->score[(equipe + 1) % 2] == 39)
			return -2;
		if (proba >= 0.9)
			return -2;
		else
			return 1;
		break;
	case -3://Iduki
		if (mise_totale == 2 && proba >= 0.87)
			return 2;
		if (mise_totale == 2 && proba < 0.87)
			return -3;
		if (mise_totale >= 2) {
			if (proba >= 0.95)
				return 2;
			else
				return -3;
		}
		break;
	default://Mise
		if (partie->score[(equipe + 1) % 2] + mise_en_jeu >= 40 || partie->score[(equipe + 1) % 2] == 39)
			return -1;
		if (mise_totale == 2 && proba >= 0.87)
			return 2;
		if (mise_totale == 2 && proba >= 0.8)
			return -3;
		if (mise_totale == 2 && proba < 0.8)
			return 1;
		if (mise_totale >= 2) {
			if (proba >= 0.95)
				return 2;
			else if (proba >= 0.87)
				return -3;
			else
				return 1;
		}
		break;
	}
	return 0;
}

int phase_mise_IA_jeu(Partie *partie, Joueur j, int mise_precedente, int mise_totale, int mise_en_jeu) {
	float proba = proba_gagner_jeu(partie, j);
	int equipe = j.num_joueur % 2;
	switch (mise_precedente) {
	case 0: //Paso avant
		if (proba >= 0.51 && partie->score[(equipe + 1) % 2] == 39)
			return -1;
		if (partie->score[(equipe + 1) % 2] + mise_en_jeu >= 40 || partie->score[(equipe + 1) % 2] == 39)
			return -1;
		if (proba >= 0.51)
			return 2;
		else
			return 0;
		break;
	case 1://Tira
		if (proba >= 0.51)
			return -3;
		else
			return 1;
		break;
	case -1://Hordago
		if (partie->score[(equipe + 1) % 2] + mise_en_jeu >= 40 || partie->score[(equipe + 1) % 2] == 39)
			return -2;
		if (proba >= 0.95)
			return -2;
		else
			return 1;
		break;
	case -3://Iduki partenaire
		if (mise_totale == 2 && proba >= 0.7)
			return 2;
		if (mise_totale == 2 && proba < 0.7)
			return -3;
		if (mise_totale >= 2) {
			if (proba >= 0.95)
				return 2;
			else
				return -3;
		}
		break;
	default://Mise
		if (partie->score[(equipe + 1) % 2] + mise_en_jeu >= 40 || partie->score[(equipe + 1) % 2] == 39)
			return -1;
		if (mise_totale == 2 && proba >= 0.7)
			return 2;
		if (mise_totale == 2 && proba >= 0.51)
			return -3;
		if (mise_totale == 2 && proba < 0.51)
			return 1;
		if (mise_totale >= 2) {
			if (proba >= 0.95)
				return 2;
			else if (proba >= 0.7)
				return -3;
			else
				return 1;
		}
		break;
	}
	return 0;
}

int phase_mise_IA_faux_jeu(Partie *partie, Joueur j, int mise_precedente, int mise_totale, int mise_en_jeu) {
	float proba = proba_gagner_faux_jeu(partie, j);
	int equipe = j.num_joueur % 2;
	switch (mise_precedente) {
	case 0: //Paso avant
		if (partie->score[equipe] + 15 <= partie->score[(equipe + 1) % 2] && partie->score[(equipe + 1) % 2] >= 25)
			return -1;
		if (proba >= 0.70 && partie->score[(equipe + 1) % 2] == 39)
			return -1;
		if (partie->score[(equipe + 1) % 2] + mise_en_jeu >= 40 || partie->score[(equipe + 1) % 2] == 39)
			return -1;
		if (proba >= 0.70)
			return 2;
		else
			return 0;
		break;
	case 1://Tira
		if (proba >= 0.75)
			return -3;
		else
			return 1;
		break;
	case -1://Hordago
		if (partie->score[(equipe + 1) % 2] + mise_en_jeu >= 40 || partie->score[(equipe + 1) % 2] == 39)
			return -2;
		if (proba >= 0.97)
			return -2;
		else
			return 1;
		break;
	default://Mise
		if (partie->score[(equipe + 1) % 2] + mise_en_jeu >= 40 || partie->score[(equipe + 1) % 2] == 39)
			return -1;
		if (partie->score[equipe] + 15 <= partie->score[(equipe + 1) % 2] && partie->score[(equipe + 1) % 2] >= 25)
			return -1;
		if (mise_totale == 2 && proba >= 0.82)
			return 2;
		else if (mise_totale == 2 && proba >= 0.70)
			return -3;
		if (mise_totale == 2 && proba < 0.70)
			return 1;
		if (mise_totale >= 2) {
			if (proba >= 0.97)
				return 2;
			if (proba >= 0.82)
				return -3;
			else
				return 1;
		}
		break;
	}
	return 0;
}

int phase_de_mise_IA(Partie *partie, Phase *phase, int mise_precedente, int mise_totale, int miseur, int mise_en_jeu) {
	switch (phase->phase) {
	case 0:
		return phase_mise_IA_grand(partie, partie->joueurs[miseur], mise_precedente, mise_totale, mise_en_jeu);
	case 1:
		return phase_mise_IA_petit(partie, partie->joueurs[miseur], mise_precedente, mise_totale, mise_en_jeu);
	case 2:
		return phase_mise_IA_pair(partie, partie->joueurs[miseur], mise_precedente, mise_totale, mise_en_jeu);
	case 3:
		return phase_mise_IA_jeu(partie, partie->joueurs[miseur], mise_precedente, mise_totale, mise_en_jeu);
	default:
		return phase_mise_IA_faux_jeu(partie, partie->joueurs[miseur], mise_precedente, mise_totale, mise_en_jeu);
	}
}






