import re  
import os
from flask import Flask, render_template, request, redirect, url_for, session, flash
from flask_mysqldb import MySQL
import MySQLdb.cursors

app = Flask(__name__) 

app.secret_key = 'abcdefgh'
  
app.config['MYSQL_HOST'] = 'db'
app.config['MYSQL_USER'] = 'root'
app.config['MYSQL_PASSWORD'] = 'password'
app.config['MYSQL_DB'] = 'cs353hw4db'

mysql = MySQL(app)  

@app.route('/')

@app.route('/login', methods =['GET', 'POST'])
def login():
    message = ''
    if request.method == 'POST' and 'username' in request.form and 'password' in request.form:
        username = request.form['username']
        password = request.form['password']
        cursor = mysql.connection.cursor(MySQLdb.cursors.DictCursor)
        cursor.execute('SELECT * FROM customer WHERE name = % s AND cid = % s', (username, password, ))
        user = cursor.fetchone()
        if user:              
            session['loggedin'] = True
            session['userid'] = user['cid']
            session['username'] = user['name']
            message = 'Logged in successfully!'
            return redirect(url_for('main_page'))
        else:
            message = 'Please enter correct email / password !'
    return render_template('login.html', message = message)

@app.route('/register', methods=['GET', 'POST'])
def register():
    message = ''
    if request.method == 'POST':
        username = request.form.get('username')
        password = request.form.get('password')  # In this context, password is actually the cid
        bdate = request.form.get('bdate')
        city = request.form.get('city')
        nationality = request.form.get('nationality')

        if not username or not password or not bdate or not city or not nationality:
            message = 'Please fill out the form!'
        else:
            cursor = mysql.connection.cursor(MySQLdb.cursors.DictCursor)
            cursor.execute('SELECT * FROM customer WHERE name = %s', (username, ))
            account_exists = cursor.fetchone()
            if account_exists:
                message = 'Account already exists!'
            else:
                cursor.execute('INSERT INTO customer (cid, name, bdate, city, nationality) VALUES (%s, %s, %s, %s, %s)',
                               (password, username, bdate, city, nationality))
                mysql.connection.commit()
                message = 'User successfully registered! Now you can login to the system!'
    return render_template('register.html', message=message)

@app.route('/main')
def main_page():
    if 'loggedin' in session:
        userid = session['userid']
        cursor = mysql.connection.cursor(MySQLdb.cursors.DictCursor)
        cursor.execute('SELECT a.aid, a.branch, a.balance, a.openDate FROM account a INNER JOIN owns o ON a.aid = o.aid WHERE o.cid = %s', (userid,))
        accounts = cursor.fetchall()
        return render_template('main_page.html', accounts=accounts)
    return redirect(url_for('login'))

@app.route('/money_transfer', methods=['GET', 'POST'])
def money_transfer():
    if 'loggedin' not in session:
        return redirect(url_for('login'))

    if request.method == 'POST':
        from_account = request.form.get('FromAccount')
        to_account = request.form.get('ToAccount')
        transfer_amount = request.form.get('TransferAmount', type=float)

        if not from_account or not to_account or not transfer_amount:
            flash('All fields are required.', 'danger')
            return redirect(url_for('money_transfer'))

        message, category = transfer_money(from_account, to_account, transfer_amount, session['userid'])
        flash(message, category)
        return redirect(url_for('money_transfer'))

    cursor = mysql.connection.cursor(MySQLdb.cursors.DictCursor)

    cursor.execute('SELECT aid, branch, balance, openDate FROM account')
    all_accounts = cursor.fetchall()

    cursor.execute('SELECT account.aid, account.branch, account.balance, account.openDate FROM account JOIN owns ON account.aid = owns.aid WHERE owns.cid = %s', (session['userid'],))
    user_accounts = cursor.fetchall()

    return render_template('money_transfer.html', all_accounts=all_accounts, user_accounts=user_accounts)

def transfer_money(from_account, to_account, transfer_amount, user_id):
    try:
        cursor = mysql.connection.cursor(MySQLdb.cursors.DictCursor)
        mysql.connection.begin()

        cursor.execute('SELECT balance FROM account JOIN owns ON account.aid = owns.aid WHERE account.aid = %s AND owns.cid = %s', (from_account, user_id))
        account = cursor.fetchone()
        if not account:
            return 'You do not own the from account', 'danger'

        if account['balance'] < transfer_amount:
            return 'Insufficient balance for the transfer', 'danger'

        cursor.execute('UPDATE account SET balance = balance - %s WHERE aid = %s', (transfer_amount, from_account))
        cursor.execute('UPDATE account SET balance = balance + %s WHERE aid = %s', (transfer_amount, to_account))

        mysql.connection.commit()

        return 'Transfer completed successfully', 'success'

    except Exception as e:
        mysql.connection.rollback()
        return 'Transfer failed: ' + str(e), 'danger'


@app.route('/close_account/<aid>', methods=['GET', 'POST'])
def close_account(aid):
    if 'loggedin' in session:
        cursor = mysql.connection.cursor(MySQLdb.cursors.DictCursor)

        cursor.execute('SELECT * FROM owns WHERE aid = %s AND cid = %s', (aid, session['userid'],))
        account = cursor.fetchone()

        if account:
            cursor.execute('DELETE FROM owns WHERE aid = %s', (aid,))

            cursor.execute('DELETE FROM account WHERE aid = %s', (aid,))

            mysql.connection.commit()

            flash('Account closed successfully along with all its ownership records.', 'success')
        else:
            flash('Error: Account not found or does not belong to you.', 'danger')
    else:
        flash('Please log in to view this page.', 'danger')

    return redirect(url_for('main_page'))

@app.route('/account_summary')
def account_summary():
    if 'loggedin' not in session:
        return redirect(url_for('login'))
    cid = session['userid']
    cursor = mysql.connection.cursor(MySQLdb.cursors.DictCursor)

    # Query 1
    cursor.execute(
        'SELECT account.aid AS aid, account.branch AS branch, account.balance AS balance, account.openDate AS openDate FROM account JOIN owns ON account.aid = owns.aid WHERE owns.cid = %s ORDER BY account.openDate ASC',
        (cid,))
    accounts = cursor.fetchall()

    # Query 2
    cursor.execute(
        'SELECT account.aid AS aid, account.balance AS balance, account.openDate AS openDate FROM account JOIN owns ON account.aid = owns.aid WHERE owns.cid = %s AND account.balance > 50000 AND account.openDate > "2015-12-31"',
        (cid,))
    high_balance_accounts = cursor.fetchall()

    # Query 3
    cursor.execute(
        'SELECT account.aid AS aid, account.balance AS balance FROM account JOIN owns ON account.aid = owns.aid JOIN customer ON owns.cid = customer.cid WHERE customer.cid = %s AND account.city = customer.city',
        (cid,))
    same_city_accounts = cursor.fetchall()

    # Query 4
    cursor.execute(
        'SELECT MAX(account.balance) AS max_balance, MIN(account.balance) AS min_balance FROM account JOIN owns ON account.aid = owns.aid WHERE owns.cid = %s',
        (cid,))
    balance_range = cursor.fetchone()

    return render_template('account_analysis.html', accounts=accounts, high_balance_accounts=high_balance_accounts,
                           same_city_accounts=same_city_accounts, balance_range=balance_range)

@app.route('/logout')
def logout():
    session.clear()
    return redirect(url_for('login'))

if __name__ == "__main__":
    port = int(os.environ.get('PORT', 8000))
    app.run(debug=True, host='0.0.0.0', port=port)
