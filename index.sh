# Generate index.md file

echo '# Julian Noter'
echo

# Make toc
HTML_FILES=$@

for url in $HTML_FILES; do
	echo "- [$url]($url)"
done

