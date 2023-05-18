cp -r content backup
python3 make-ugly.py content
make kactl
rm -rf content
cp -r backup content
rm -rf backup
