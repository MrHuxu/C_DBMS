<?xml version="1.0"?>
<anjuta>
    <plugin name="GNU Debugger" mandatory="no">
        <require group="Anjuta Plugin"
                 attribute="Location"
                 value="anjuta-gdb:GdbPlugin"/>
    </plugin>
    <plugin name="Terminal" mandatory="no">
        <require group="Anjuta Plugin"
                 attribute="Location"
                 value="anjuta-terminal:TerminalPlugin"/>
    </plugin>
    <plugin name="Code Snippets" mandatory="no">
        <require group="Anjuta Plugin"
                 attribute="Location"
                 value="anjuta-snippets-manager:SnippetsManagerPlugin"/>
    </plugin>
</anjuta>
