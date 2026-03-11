from flask import Flask, render_template, request, redirect, url_for, session
import os

app = Flask(__name__, static_url_path='/static')

app.secret_key = os.urandom(24)  # Vous pouvez également définir une clé secrète statique si vous préférez

mapstr = ""

# Fonction pour ajouter un utilisateur au fichier texte
def add_user_to_file(pseudo, password, mail):
    with open("acount.txt", "r") as f:
        for line in f:
            if line.split(' ')[0] == pseudo:
                return False

    with open("acount.txt", "a") as f:
        f.write(f"{pseudo} {password} {mail} 0\n")
    return True

def verify_credentials(username, password):
    with open('acount.txt', 'r') as file:
        for line in file:
            l = line.split(' ')
            stored_username = l[0] 
            stored_password = l[1]
            if stored_username == username and stored_password == password:
                return True
    return False

@app.route('/login', methods=['POST'])
def login():
    username = request.form['username']
    password = request.form['password']
    
    if verify_credentials(username, password):
        session['username'] = username
        return redirect(url_for('my_account'))
    else:
        return render_template('login.html', error="Identifiants invalides!")

@app.route('/my_account')
def my_account():
    if 'username' not in session:
        return redirect(url_for('register'))

    username = session['username']
    nmonth = 0

    # Vérification abonnement
    with open('acount.txt', 'r') as file:
        for line in file:
            l = line.strip().split(' ')
            if l[0] == username:
                nmonth = int(l[3])
                break

    if nmonth == 0:
        return "Pour jouer il faut payer (1€ / mois)"

    worlds_data = []

    for i in range(1, 13):
        character = None

        with open(f'world/m{i}.txt', 'r') as file:
            for line in file:
                l = line.strip().split(' ')
                if l[0] == '0' and l[11] == username:
                    character = {
                        "name": l[12]
                    }
                    break

        worlds_data.append({
            "world": i,
            "start_hour": (i - 1) * 2,
            "end_hour": i * 2,
            "character": character
        })

    return render_template("my_account.html", worlds=worlds_data)


@app.route('/create_character.html', methods=['POST'])
def create_character():
    if 'username' not in session:
        return redirect(url_for('register'))

    username = session['username']

    world = request.form['world']
    nom = request.form['name']
    sexe = request.form['sex']
    peau = request.form['skin']
    gabarit = request.form['size']

    new_line = f"{world} {username} {nom} {sexe} {peau} {gabarit}\n"

    lines = []

    # Lire les anciennes demandes si le fichier existe
    try:
        with open("request.txt", "r") as f:
            lines = f.readlines()
    except FileNotFoundError:
        pass  # Le fichier sera créé plus bas

    updated = False
    new_lines = []

    for line in lines:
        l = line.strip().split(" ")

        # Si même monde ET même username → on écrase
        if l[0] == world and l[1] == username:
            new_lines.append(new_line)
            updated = True
        else:
            new_lines.append(line)

    # Si aucune ancienne demande trouvée → on ajoute
    if not updated:
        new_lines.append(new_line)

    # Réécriture complète du fichier
    with open("request.txt", "w") as f:
        f.writelines(new_lines)

    return redirect(url_for('my_account'))

# Route d'inscription
@app.route('/register.html', methods=['GET', 'POST'])
def register():
    if 'username' in session:
        return redirect(url_for('my_account'))
    else:
        if request.method == 'POST':
            # Récupérer les données du formulaire
            pseudo = request.form['pseudo']
            password = request.form['password']
            mail = request.form['email']  

            # Ajouter l'utilisateur au fichier
            if add_user_to_file(pseudo, password, mail) == True:
            
            # Rediriger l'utilisateur vers une page de confirmation (ou autre page)
                return redirect(url_for('success'))
            else:
                return render_template('register.html', error="An account with the same name already exist")
    return render_template('register.html')

@app.route('/img/img1.png', methods=['GET', 'POST'])
def get_img_1():
    return render_template('img/img1.png')    

# Route de confirmation après l'inscription
@app.route('/success')
def success():
    return "Inscription réussie ! Vous êtes maintenant inscrit."

@app.route('/login.html')
def index():
    if 'username' in session:
        return redirect(url_for('my_account'))
    else:
        return render_template('login.html')

@app.route('/')
def home():
    return render_template('index.html')

@app.route('/logout')
def logout():
    # Déconnecter l'utilisateur en supprimant la session
    session.pop('username', None)
    return redirect(url_for('index'))

if __name__ == '__main__':
    app.run(debug=True)
