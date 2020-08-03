class User:
    def __init__(self, username, email, last_name, first_name, birthday, bio, role, mail_confirmed=False):
        self.username = username
        self.email = email
        self.last_name = last_name
        self.first_name = first_name
        self.birthday = birthday
        self.bio = bio
        self.role = role
        self.mail_confirmed = mail_confirmed


