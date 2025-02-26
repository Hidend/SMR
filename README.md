
# SMR

**SMR** es un mod rápido para bloquear ciertos mensajes. Utiliza patrones de expresiones regulares para filtrar y bloquear mensajes según configuraciones específicas.

## Comandos

- `/smr` - Activar o desactivar el sistema de filtrado de mensajes.
- `/smrd` - Ver los mensajes bloqueados y el color de la línea.
- `/smrr` - Recargar la configuración desde el archivo `smr_config.json`.

## Configuración

Debes tener un archivo llamado `smr_config.json` en la raíz del GTA. El formato del archivo debe ser el siguiente:

```json
{
    "patterns": [
        {
            "pattern": "^\\[\\[ Sube",
            "color": 4294901930
        },
        {
            "pattern": "hola321"
        }
    ]
}
```

### Descripción de los Campos

-   **pattern**: Expresión regular que define el patrón del mensaje a bloquear.
-   **color** (opcional): Color asociado al mensaje bloqueado. Si no se especifica, todo mensaje que contenga la expresión regular se bloqueará independientemente del color.

Puedes ver qué mensajes se bloquearían sin realmente bloquearlos usando `/smr` y `/smrd` al mismo tiempo, solo para tu información.

## Agradecimientos

-   Gracias a BH por SAMP-API
-   Gracias a kin4stat por ktsignal y kthook
-   Gracias a imring por RakHook
-   Gracias a nlohmann por su increíble biblioteca JSON
-   Gracias a anwuPP por la plantilla también

(README generado por ChatGPT, demasiado perezoso para esto, lulz)

----------

# SMR

**SMR** is a quick mod I made to block certain messages. It uses regular expression patterns to filter and block messages based on specific configurations.

## Commands

-   `/smr` - Toggle the message filtering system on or off.
-   `/smrd` - View blocked messages and their line color.
-   `/smrr` - Reload the configuration from the `smr_config.json` file.

## Configuration

You need to have a file named `smr_config.json` in the root directory of GTA. The file format should be as follows:

```json
`{
    "patterns": [
        {
            "pattern": "^\\[\\[ Sube",
            "color": 4294901930
        },
        {
            "pattern": "hola321"
        }
    ]
}
``` 

### Field Descriptions

-   **pattern**: Regular expression that defines the pattern of the message to block.
-   **color** (optional): Color associated with the blocked message. If not specified, any message containing the regular expression will be blocked regardless of color.

You can see which messages would be blocked without actually blocking them by using `/smr` and `/smrd` at the same time, just FYI.

## Thanks

-   Thanks to BH for SAMP-API
-   Thanks to kin4stat for ktsignal and kthook
-   Thanks to imring for RakHook
-   Thanks to nlohmann for your awesome JSON library
-   Thanks to anwuPP for the template too

(README generated by ChatGPT, too lazy for this lulz)⌢匠前•਍