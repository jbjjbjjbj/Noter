# Generate index.md file

echo '# Julian Noter'
echo

echo 'Or just use your [browser build in file explorer](.)'
echo

cat << EOF
<input type="text" id="search" onkeyup="filter(event)" placeholder="Search">

EOF

# Make toc
HTML_FILES=$@

for url in $HTML_FILES; do
	echo "- [$url]($url)"
done

cat << EOF

<script>
function filter(e) {
	var li = document.getElementsByTagName('li');


	var input = document.getElementById('search');
	var filter = input.value.toUpperCase();

	for (i = 0; i < li.length; i++) {
		var a = li[i].getElementsByTagName("a")[0];
		txtValue = a.textContent || a.innerText;
		if (txtValue.toUpperCase().indexOf(filter) > -1) {
			li[i].style.display = "";
			if( e.key == "Enter") {
				window.location.href = a.href;
				return;
			}
		} else {
			li[i].style.display = "none";
		}
	}
}

</script>
EOF

