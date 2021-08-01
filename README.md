*Dont use enso with this, it will probably bootloop / freeze the console*

# nand-dumper

Dumps the PSVita's entire decrypted NAND (sdstor0:/int-lp-act-entire)
to ux0:/int-lp-act-entire.img 

its roughly 3.6GB, so make sure you have enough space on your ux0 partition

useful for recovering deleted data (either by you, or by the system itself)
ex, this was used to get 3.72 Devkit update, by running this on a devkit then looking in ur0 raw partition

(note: System will freeze while the plugin is running, and then will automatically reboot the system when done,
recommended to use Xerpi Plugin Loader) 

Please dont attempt to restore a NAND backup made, as doing this is very likely to just brick your console 
