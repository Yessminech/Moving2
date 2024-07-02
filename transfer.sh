#!/bin/bash

# Konfigurationsparameter
REMOTE_USER="username"          # Remote-Benutzername
REMOTE_HOST="hostname_or_ip"    # Remote-Host oder IP-Adresse
REMOTE_DIR="/path/to/remote/dir" # Zielverzeichnis auf dem Remote-Server
LOCAL_DIR="/path/to/local/dir"   # Verzeichnis der zu übertragenden Dateien

# Dateien übertragen
scp -r "$LOCAL_DIR"/* "$REMOTE_USER@$REMOTE_HOST:$REMOTE_DIR"

# Übertragungsstatus prüfen
if [ $? -eq 0 ]; then
  echo "Dateien wurden erfolgreich übertragen."
else
  echo "Fehler bei der Übertragung der Dateien."
fi
