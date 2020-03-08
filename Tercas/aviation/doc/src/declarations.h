#ifndef DECLARATIONS_H
#define DECLARATIONS_H

#define MYSQL
#define MYSQL_DATABASE "aviaDocs"
#define MYSQL_TABLE "doc"

enum Columns {
    doc_id,
    doc_section_id,
    doc_doc,
    doc_verNum,
    doc_verDate,
    doc_org_id,
    doc_issueNum,
    doc_issueDate,
    doc_note,
    doc_tags,
    org_orgRu
};

#endif // DECLARATIONS_H
