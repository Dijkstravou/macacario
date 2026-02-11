set ts=4 sw=4 mouse=a nu rnu ai si et undofile
syntax on

"inoremap ( ()<left>
"inoremap [ []<left>
"inoremap { {<cr>}<esc>ko
"inoremap <C-p> {}<left>
inoremap <C-j> <esc>la
inoremap <tab> <esc>
inoremap <S-tab> <tab>

function H(l)
	return system("sed '/^#/d' | cpp -dD -P -fpreprocessed | tr -d '[:space:]' | md5sum", a:l)
endfunction
function P() range
	for i in range(a:firstline, a:lastline)
		let l = getline(i)
		call cursor(i, len(l))
		echo H(getline(search('{}'[1], 'bc', i) ? searchpair('{', '', '}', 'bn') : i, i))[0:2] l
	endfor
endfunction
vmap <C-H> :call P()<CR>

colorscheme sorbet
