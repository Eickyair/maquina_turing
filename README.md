
# Devcontainer
 * Este código utiliza un devcontainer para compilar y ejecutar el programa.
 * Un devcontainer es un entorno de desarrollo aislado y reproducible que se ejecuta en un contenedor de Docker.
 * Al utilizar un devcontainer, ya no es necesario instalar el compilador GCC en la máquina local.
 * Esto tiene varias ventajas:
    - Evita conflictos con otras versiones de GCC o dependencias en el sistema.
    - Permite tener un entorno de desarrollo consistente en diferentes máquinas.
    - Facilita la configuración manteniendo un entorno de desarrollo con otros programadores identico.
    - Asegura que todas las dependencias necesarias están disponibles y configuradas correctamente.
 * Para utilizar un devcontainer, se debe tener instalado Docker en la máquina local.
 * Luego, se puede configurar el devcontainer mediante un archivo de configuración llamado "devcontainer.json".
 * Este archivo especifica la imagen de Docker a utilizar, las extensiones de VS Code a instalar, entre otras configuraciones.
 * Una vez configurado, se puede abrir el proyecto en un contenedor de desarrollo utilizando la opción "Reopen in Container" en VS Code.
 * Esto iniciará el contenedor de Docker con el entorno de desarrollo configurado y se podrá compilar y ejecutar el programa sin problemas.
# Preparar el Entorno

### Pasos para instalar Docker:
1. Visita el sitio web oficial de Docker (https://www.docker.com/) y descarga la versión adecuada para tu sistema operativo.
2. Sigue las instrucciones de instalación proporcionadas por Docker para tu sistema operativo específico.
3. Una vez instalado Docker, verifica que esté funcionando correctamente ejecutando el comando `docker --version` en la línea de comandos.

### Pasos para instalar la extensión de DevContainer en VSCode:
1. Abre Visual Studio Code.
2. Ve a la pestaña de extensiones en el panel lateral izquierdo.
3. Busca la extension "DevContainer" desarrollada por Microsoft en la barra de búsqueda.
4. Haz clic en "Instalar".
5. Espera a que la instalación se complete y reinicia VSCode si es necesario.

### Pasos para abrir el entorno en un Dev Container:
1. Abre el proyecto en Visual Studio Code.
2. Ve al menú "View" y selecciona "Command Palette" (o presiona Ctrl+Shift+P en Windows/Linux o Cmd+Shift+P en macOS).
3. Escribe "dev container" y busca la opccion de "Open Folder in...".
4. Selecciona la carpeta del proyecto que deseas abrir en un Dev Container.
5. Espera a que se construya el contenedor y se abra el entorno de desarrollo en el contenedor.

# Ejecucion
Para ejecutar el programa a través se creo el script <code>run.sh</code>:

1. Asegúrate de tener los permisos de ejecución para el script. Si no los tienes, puedes otorgarlos utilizando los siguientes comandos:
<pre>
  #para convertirse en el usuario root
  #por defecto el devcontainer esta el usario vscode
  sudo su
  chmod +x run.sh
  # Salir del usario root
  exit
</pre>
2. Una vez que tengas los permisos de ejecución, puedes ejecutar el programa utilizando el siguiente comando en la terminal:
<pre>
  ./run.sh
</pre>
