TEMPLATE=aux

include(../options.pri)

PROJECT=TelegramQt
QDOCCONF=$${PROJECT}.qdocconf

QDOC = $$[QT_INSTALL_BINS]/qdoc
QHELPGENERATOR = $$[QT_INSTALL_BINS]/qhelpgenerator

QDOC_OUTPUT = $${OUT_PWD}/html
QHELPFILE = $${QDOC_OUTPUT}/$${PROJECT}.qhp
QCHFILE = $${QDOC_OUTPUT}/$${PROJECT}.qch

DOC_ENV = QT_INSTALL_DOCS=$$[QT_INSTALL_DOCS]

qch_docs.target = $${QCHFILE}
qch_docs.depends += FORCE
qch_docs.commands =  (env $$DOC_ENV $$QDOC $${PWD}/$${QDOCCONF} --outputdir=$${QDOC_OUTPUT}) && \
    ($${QHELPGENERATOR} $${QHELPFILE} -o $${QCHFILE})

docs.depends = $${QCHFILE}
docs.path = $${INSTALL_DOC_DIR}
docs.commands = $$QMAKE_INSTALL_FILE $${QCHFILE} $(INSTALL_ROOT)$${docs.path}

QMAKE_EXTRA_TARGETS += qch_docs docs
INSTALLS += docs

OTHER_FILES += $${QDOCCONF}
