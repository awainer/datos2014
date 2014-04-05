#!/bin/bash
find . -name '*.o' -exec rm -rf {} \;
find . -name '*.deps' -exec rm -rf {} \;
echo "listo para compilar y ejecutar!!! ;D"
