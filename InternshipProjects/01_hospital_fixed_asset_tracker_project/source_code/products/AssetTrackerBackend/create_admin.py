"""
File: create_admin.py
Author: Farros Ramzy (you@domain.com)
Description: Command-line utility for creating an administrator account in the database.
Version: 0.1
Date: 2026-05-18

Copyright (c) 2026
"""
from app.database import Base, engine, SessionLocal
from app.db_models import User
from app.services.authority.auth_service import hash_password


Base.metadata.create_all(bind=engine)

db = SessionLocal()

try:
    existing = db.query(User).filter(User.email == "admin@hospital.local").first()

    if existing:
        print("Admin user already exists.")
    else:
        admin = User(
            email="admin@hospital.local",
            full_name="System Administrator",
            role="admin",
            hashed_password=hash_password("Admin12345!"),
            is_active=True,
        )

        db.add(admin)
        db.commit()

        print("Admin user created.")
        print("Email: admin@hospital.local")
        print("Password: Admin12345!")

finally:
    db.close()
