# $FreeBSD$

.if !target(__<bsd.init.mk>__)
.error bsd.links.mk cannot be included directly.
.endif

.if defined(NO_ROOT)
.if !defined(TAGS) || ! ${TAGS:Mpackage=*}
TAGS+=         package=${PACKAGE}
.endif
TAG_ARGS=      -T ${TAGS:[*]:S/ /,/g}
.endif

afterinstall: _installlinks
.ORDER: realinstall _installlinks
# If the source and destination file are the same file (e.g. Mail/mail on a
# case-insensitive file-system) we have to pass -S to install(1) to avoid
# deleting the source file.
_installlinks:
.for s t in ${LINKS}
.if ${s:tl} == ${t:tl}
	if test "${DESTDIR}${t}" -ef "${DESTDIR}${s}"; then \
		echo "Note: requested hard link from ${t} to ${s} on case-insensitive file system."; \
	fi
	${INSTALL_LINK} -S ${TAG_ARGS} ${DESTDIR}${s} ${DESTDIR}${t}
.else
	${INSTALL_LINK} ${TAG_ARGS} ${DESTDIR}${s} ${DESTDIR}${t}
.endif
.endfor
.for s t in ${SYMLINKS}
.if ${s:tl} == ${t:tl}
	if test "${DESTDIR}${t}" -ef "${DESTDIR}${s}"; then \
		echo "Note: requested symlink from ${t} to ${s} on case-insensitive file system."; \
	fi
	${INSTALL_SYMLINK} -S ${TAG_ARGS} ${s} ${DESTDIR}${t}
.else
	${INSTALL_SYMLINK} ${TAG_ARGS} ${s} ${DESTDIR}${t}
.endif
.endfor
