"""Academic report assembly/rendering. Assignment implementations remain C++17."""
from pathlib import Path
import html
import json
import re
import textwrap

ROOT=Path(__file__).resolve().parents[1]
REPORT=ROOT/'Report'
REPORT.mkdir(exist_ok=True)
URL='https://github.com/hosheapaul2006/DSA0110_SLOT-B-192471019-Assignment-2'

TITLES={1:'Call by Value, by Reference and by Pointer',2:'Return by Reference and Its Dangers',
        3:'Default Arguments and Function Overloading',4:'Savings Account Mini-Statement',
        5:'Static Members and Arrays of Objects',6:'Friend Functions and Inline Functions',
        7:'Diagnose, Redesign and Validate'}
QUESTIONS={
1:'Hostel fee concessions: implement value/reference/pointer passing, predict caller changes, defend the update interface, predict the supplied program, complete the reference TODO and compare copied storage. PDF pages 2-5; 6 marks.',
2:'Examination marks register: return the highest element by reference, contrast copy/const-reference/index/pointer returns, capture a local-reference warning and evaluate vector growth. PDF pages 5-6; 4 marks.',
3:'Courier calculator: diagnose ambiguous declarations, combine defaults with int-grams/double-kg/Parcel overloads, predict six selections and compare a request structure and template. PDF page 6; 6 marks.',
4:'Savings account: private account/balance/ten-transaction array/count, inside/outside member definitions, correct last-ten retention, 11th transaction handling and capacity50 alternatives. PDF page 7; 6 marks.',
5:'Bus tickets: derive static state from the shared-data principle, construct an oversized array, show waiting and static persistence, predict Token and complete the supplied TODOs. PDF pages 7-11; 7 marks.',
6:'Train planner: compare private clock times with friends, complete absolute-difference/earlier TODOs, test noon/equality, measure ten million calls with/without inline under both flags and defend deployment. PDF pages 11-13; 8 marks.',
7:'Use evidence from Q1-Q6 to diagnose one growing limitation, define an objective, design and predict a revision before implementation, compare it fairly and defend the outcome. Address A-F individually. PDF pages 13-14; 13 marks.'}

def read(path): return (ROOT/path).read_text(encoding='utf-8-sig')
def code(path,language='cpp'): return f'### {Path(path).name}\n\n```{language}\n'+read(path).rstrip()+ '\n```\n\n'
def subordinate(text):
    return re.sub(r'^(#{1,4}) ',lambda m:'#'*(len(m[1])+1)+' ',text,flags=re.M)

def make_markdown():
    audit=json.loads(read('Reference/final_audit.json'))
    sections=['# DSA0110 - Assignment 2 (CO2)\n\nStudent: D Hoshea Paul\n\nRegister Number: 192471019\n\nSlot: B\n\nGitHub Repository: '+URL+'\n\n',
    '## Scope, environment and evidence\n\nOriginal problem statement: Reference/ASSIGNMENT 2.pdf, 15 pages, Q1-Q7, total 50 marks. Every question and Q7 section A-F is addressed. This report is supported by the complete C++ sources and raw evidence in the task folders.\n\n',
    'Actual local execution date: 10 November 2026. Compiler: GCC 14.2.0 (WinLibs MinGW-w64 x86_64 UCRT POSIX SEH). Standard build: `g++ -std=c++17 -Wall -Wextra -Wpedantic -O0 source.cpp -o program.exe`. Benchmark builds also use `-O2`. Hardware/platform information is recorded below without personal machine identifiers.\n\n',
    '```text\n'+read('Reference/platform.txt').strip()+'\nCPU: '+read('Reference/processor.txt').strip()+'\n```\n\n',
    f"Local evidence: {audit['valid_source_count']} valid C++ source programs, {audit['build_run_configurations']} successful build/run configurations, two diagnostic-only sources, 12 actual Programiz program runs and 19 current genuine screenshots. Eight earlier screenshots remain with their initial execution records for provenance. The unsafe local-reference source was compiled but not executed.\n\n",
    'Console demonstrations show coursework results; validation labels appear in separate validation sources/logs and test tables. Python scripts only orchestrate compilation, evidence auditing and report layout; they do not implement assignment solutions. No original prediction was rewritten after execution.\n\n',
    '### Prediction chronology\n\n| Prediction | Commit before execution | Outcome |\n|---|---|---|\n| Q1 supplied output and stored fees | c2a6ade | Matched |\n| Q3 six overload selections | c9dd5c2 | Matched original validation output |\n| Q5 Token | cbc5040 | Matched |\n| Q7 performance objective/prediction | a8e1a25 | Objective achieved; raw trials retained |\n\n',
    'The later console presentation change is documented in Reference/PREDICTION_HISTORY.md. The original Q3 prediction includes validation labels and belongs to the preserved original source now named validation.cpp; it is not presented as a prediction of the later clean-output main.cpp. Windows CRLF newlines are decoded to LF for comparisons; all other spaces and characters are retained. Programiz result-pane text was separately checked against local stdout, permitting only the platform success banner/trailing blank space after the full expected output.\n\n',
    '### Submission and compliance notes\n\nThe existing public repository name is preserved at the user\'s request. The PDF requests DSA01-192471019-Assignment2, so faculty acceptance of the different name remains pending. Its deadline is 31 October 2026; these executions and progressive commits are dated 10 November 2026, with no backdating. The user will submit Classroom personally. Classroom was signed out during the access check; no course or assignment was selected. The PDF also requires the student to execute every task individually: these automated/browser-operated executions do not certify that personal step.\n\n']
    for i in range(1,8):
        folder=f'Task{i:02}'
        sections += [f'# Q{i} - {TITLES[i]}\n\n','## Problem statement and objective\n\n'+QUESTIONS[i]+'\n\n',subordinate(read(folder+'/explanation.md'))+'\n\n','## Primary C++17 source\n\n']
        sections += [code(folder+('/programiz_demo.cpp' if i==7 else '/main.cpp'))]
        if i in [1,5]:
            sections += ['## Supplied output prediction\n\n',code(folder+'/predict_output.cpp'), 'Exact prediction saved before execution:\n\n',code(folder+'/outputs/predicted_output.txt','text'), 'Actual output:\n\n',code(folder+'/outputs/predict_output_actual.txt','text')]
            sections += [subordinate(read(folder+('/outputs/stored_fee_predictions.md' if i==1 else '/outputs/prediction_reasoning.md')))+'\n\n']
        if i==3:
            sections += ['## Original overload prediction and diagnostic\n\n',subordinate(read(folder+'/outputs/overload_predictions.md'))+'\n\n',code(folder+'/outputs/predicted_output.txt','text'),code(folder+'/outputs/initial_execution/main_actual.txt','text'),code(folder+'/ambiguity.cpp'),code(folder+'/outputs/ambiguity_compiler.txt','text')]
        if i in [1,5,6]:
            sections += ['## Completed supplied TODO exercise\n\nOnly TODO regions are replaced. The original extracted source is in Reference; the audit verifies preservation.\n\n',code(folder+'/complete_code.cpp'), 'Supplied expected output:\n\n',code(folder+'/outputs/complete_expected.txt','text'), 'Actual executed output:\n\n',code(folder+'/outputs/complete_code_actual.txt','text')]
        if i==2:
            sections += ['## Deliberately unsafe diagnostic-only source\n\nThis source was not executed.\n\n',code(folder+'/unsafe_local.cpp'),code(folder+'/outputs/unsafe_local_compiler.txt','text')]
        if i==4:
            sections += ['## Original growth evidence\n\n',code(folder+'/baseline_growth.cpp'),code(folder+'/outputs/baseline_growth_actual.txt','text')]
        if i in [6,7]:
            sections += ['## Measured benchmark results\n\n',subordinate(read(folder+('/benchmark_results.md' if i==6 else '/comparison.md')))+'\n\n']
        if i==7:
            sections += ['## Original pre-implementation prediction\n\n',subordinate(read(folder+'/outputs/redesign_prediction.md'))+'\n\n', '## Original and redesigned validation drivers\n\n',code(folder+'/original.cpp'),code(folder+'/redesigned.cpp')]
        sections += ['## Executed test cases\n\n',subordinate(read(folder+'/test_cases.md'))+'\n\n','## Actual console demonstration output\n\n',code(folder+('/outputs/programiz_demo_actual.txt' if i==7 else '/outputs/main_actual.txt'),'text')]
        sections += ['## Genuine Programiz evidence\n\nThe following images are actual browser captures after Run completed. The full capture files and result-pane text are retained in the repository. PDF panels show the upper portion when a full-page capture is taller than the landscape page; no output was substituted.\n\n']
        stems=['programiz_demo'] if i==7 else ['main']
        if i in [1,5]: stems+=['predict_output']
        if i in [1,5,6]: stems+=['complete_code']
        for stem in stems:
            sections += [f'![Q{i}: {stem}.cpp - actual Programiz source and output](../{folder}/screenshots/{stem}_programiz.jpg)\n\n']
    sections+=['# Benchmark source appendix\n\nComplete benchmark sources are included so the measurement methodology can be inspected and repeated. Q7 uses the same history definitions shown in its self-contained demonstration.\n\n',code('Task06/benchmark.cpp').replace('### benchmark.cpp','## Task06/benchmark.cpp',1),code('Task07/benchmark.cpp').replace('### benchmark.cpp','# Q7 benchmark source',1)]
    sections+=['# Completion and submission preparation\n\n',read('SUBMISSION_PREPARATION.md').replace('# Submission materials - review before publication/submission','## Materials and current status',1)+'\n\n',read('ASSIGNMENT_CHECKLIST.md').replace('# Assignment 2 requirement audit','## Requirement checklist',1)+'\n\n']
    sections+=['## Reproduction and evidence index\n\nREADME.md contains the exact standard, benchmark and expected-diagnostic commands. tools/run_all.py reproduces all local configurations; tools/audit.py checks predictions, source hashes, TODO-only changes, diagnostics, executed records and online output provenance. Reference/final_audit.json records 139 successful evidence checks. Every task provides explanation.md, test_cases.md, source files, outputs and screenshots. VIVA_PREPARATION.md contains concept explanations, likely questions and two practice modifications per task.\n\n',
               'The repository is the complete source/evidence record. No execution date, output, diagnostic, benchmark or screenshot is fabricated. Remaining faculty naming/deadline acceptance and student personal-execution/submission steps are explicitly listed.\n']
    result=''.join(sections)
    (REPORT/'Assignment2_Report.md').write_text(result,encoding='utf-8',newline='\n')
    return result

def render_pdf(markdown):
    from reportlab.lib import colors
    from reportlab.lib.enums import TA_CENTER
    from reportlab.lib.pagesizes import A4,landscape
    from reportlab.lib.styles import getSampleStyleSheet,ParagraphStyle
    from reportlab.platypus import (BaseDocTemplate,PageTemplate,Frame,Paragraph,Spacer,PageBreak,
                                   NextPageTemplate,Preformatted,Table,TableStyle,Flowable)
    from reportlab.platypus.tableofcontents import TableOfContents
    from reportlab.lib.utils import ImageReader
    from PIL import Image
    portrait=A4; wide=landscape(A4); margin=42
    styles=getSampleStyleSheet()
    styles.add(ParagraphStyle(name='Body',fontName='Helvetica',fontSize=9.1,leading=13,spaceAfter=6))
    styles.add(ParagraphStyle(name='Small',parent=styles['Body'],fontSize=7.6,leading=10))
    styles.add(ParagraphStyle(name='CodeBlock',fontName='Courier',fontSize=7.8,leading=10.1,spaceAfter=9,textColor=colors.black,
                             backColor=colors.HexColor('#f4f5f6'),borderPadding=6))
    styles['Heading1'].fontSize=17;styles['Heading1'].leading=22;styles['Heading1'].spaceAfter=11
    styles['Heading2'].fontSize=12.5;styles['Heading2'].leading=17
    styles['Heading3'].fontSize=10.5;styles['Heading3'].leading=14
    styles.add(ParagraphStyle(name='CoverTitle',fontName='Helvetica-Bold',fontSize=24,leading=31,alignment=TA_CENTER,spaceAfter=24))
    styles.add(ParagraphStyle(name='CoverLine',fontName='Helvetica',fontSize=12,leading=19,alignment=TA_CENTER,spaceAfter=10))

    class ReportDoc(BaseDocTemplate):
        def afterFlowable(self,flowable):
            if isinstance(flowable,Paragraph) and flowable.style.name=='Heading1' and flowable.getPlainText()!='Contents':
                self.notify('TOCEntry',(0,flowable.getPlainText(),self.page))
    def footer(canvas,doc):
        pageWidth,pageHeight=doc.pagesize
        canvas.setFont('Helvetica',7)
        canvas.setFillColor(colors.HexColor('#4b5563'))
        canvas.drawString(margin,24,'DSA0110 Assignment 2 | D Hoshea Paul | 192471019')
        canvas.drawRightString(pageWidth-margin,24,str(doc.page))
    def portrait_begin(canvas,doc): doc.pagesize=portrait;canvas.setPageSize(portrait)
    def landscape_begin(canvas,doc): doc.pagesize=wide;canvas.setPageSize(wide)
    doc=ReportDoc(str(REPORT/'Assignment2_Report.pdf'),pagesize=portrait,
                  title='DSA0110 - Assignment 2 (CO2)',author='D Hoshea Paul',
                  leftMargin=margin,rightMargin=margin,topMargin=margin,bottomMargin=40)
    def portrait_page(canvas,doc): portrait_begin(canvas,doc);footer(canvas,doc)
    def landscape_page(canvas,doc): landscape_begin(canvas,doc);footer(canvas,doc)
    doc.addPageTemplates([
        PageTemplate('portrait',[Frame(margin,40,portrait[0]-2*margin,portrait[1]-margin-40,id='portrait-frame')],onPage=portrait_page,pagesize=portrait),
        PageTemplate('landscape',[Frame(margin,40,wide[0]-2*margin,wide[1]-margin-40,id='landscape-frame')],onPage=landscape_page,pagesize=wide)])

    def safe(text):
        for old,new in [('–','-'),('—','-'),('’',"'"),('‘',"'"),('“','"'),('”','"'),('→','->'),('₹','Rs '),('\u00a0',' ')]: text=text.replace(old,new)
        return text
    def inline(text):
        text=html.escape(safe(text))
        text=re.sub(r'`([^`]+)`',r'<font name="Courier">\1</font>',text)
        text=re.sub(r'\*\*([^*]+)\*\*',r'<b>\1</b>',text)
        text=re.sub(r'\[([^\]]+)\]\(([^)]+)\)',lambda m: m[1]+' ('+m[2]+')',text)
        return text
    story=[]
    def pb():
        if story and not isinstance(story[-1],PageBreak):story.append(PageBreak())
    def switchpage(template):
        if len(story)>=2 and isinstance(story[-1],PageBreak) and isinstance(story[-2],NextPageTemplate):
            story[-2]=NextPageTemplate(template)
        else:
            story.append(NextPageTemplate(template));pb()
    def para(text,style='Body'): story.append(Paragraph(inline(text),styles[style]))
    class CapturePanel(Flowable):
        def __init__(self,path,width,height):
            Flowable.__init__(self);self.path=str(path);self.width=width;self.height=height
            self.iw,self.ih=Image.open(path).size
        def draw(self):
            scale=self.width/self.iw
            self.canv.saveState()
            clip=self.canv.beginPath();clip.rect(0,0,self.width,self.height)
            self.canv.clipPath(clip,stroke=0)
            self.canv.drawImage(ImageReader(self.path),0,self.height-self.ih*scale,width=self.width,height=self.ih*scale)
            self.canv.restoreState()
    story+=[Spacer(1,105),Paragraph('DSA0110 - Assignment 2 (CO2)',styles['CoverTitle'])]
    for line in ['Student: D Hoshea Paul','Register Number: 192471019','Slot: B','C++17 | Functions and Object-Oriented Concepts']:
        story.append(Paragraph(line,styles['CoverLine']))
    story+=[Spacer(1,30),Paragraph('GitHub Repository',styles['CoverLine']),Paragraph(URL,styles['Small']),
            Spacer(1,24),Paragraph('Actual execution and preparation: 10 November 2026',styles['CoverLine'])]
    pb();para('Contents','Heading1')
    toc=TableOfContents();toc.levelStyles=[ParagraphStyle(name='TOC0',fontName='Helvetica-Bold',fontSize=10,leading=16,spaceBefore=8),
                                         ParagraphStyle(name='TOC1',fontName='Helvetica',fontSize=8,leading=11,leftIndent=12)]
    story.append(toc);pb()
    # Cover information is already laid out above; retain all remaining Markdown content.
    body=markdown[markdown.index('## Scope, environment and evidence'):]
    lines=body.splitlines();i=0
    while i<len(lines):
        line=lines[i].strip()
        if not line:i+=1;continue
        if line.startswith('```'):
            block=[];i+=1
            while i<len(lines) and not lines[i].strip().startswith('```'):
                raw=safe(lines[i].expandtabs(4))
                block.extend(textwrap.wrap(raw,width=100,replace_whitespace=False,drop_whitespace=False,break_long_words=True,break_on_hyphens=False) or [''])
                i+=1
            story.append(Preformatted('\n'.join(block),styles['CodeBlock']));i+=1;continue
        image=re.match(r'!\[([^\]]*)\]\(([^)]+)\)',line)
        if image:
            switchpage('landscape')
            para(image[1],'Heading2')
            para('Genuine Programiz capture. Upper panel shown where the full capture is taller; the unchanged original file is included in the repository.','Small')
            width=wide[0]-2*margin-12;height=wide[1]-margin-40-75
            story.append(CapturePanel((REPORT/image[2]).resolve(),width,height))
            story.append(NextPageTemplate('portrait'));pb();i+=1;continue
        heading=re.match(r'^(#{1,6})\s+(.+)',line)
        if heading:
            level=len(heading[1]);text=heading[2]
            if level==1:pb()
            para(text,'Heading'+str(min(level,3)));i+=1;continue
        if line.startswith('|'):
            rows=[]
            while i<len(lines) and lines[i].strip().startswith('|'):
                cells=[c.strip() for c in lines[i].strip().strip('|').split('|')]
                if not all(re.fullmatch(r'[:\- ]+',c or '-') for c in cells): rows.append(cells)
                i+=1
            n=max(len(r) for r in rows)
            for row in rows: row.extend(['']*(n-len(row)))
            width=portrait[0]-2*margin-12
            if n==5: widths=[width*x for x in [.07,.28,.25,.31,.09]]
            elif n==7: widths=[width*x for x in [.06,.075,.235,.235,.13,.13,.135]]
            elif n==4: widths=[width*x for x in [.18,.27,.28,.27]]
            else:widths=[width/n]*n
            # Ensure custom fractions sum to the available width.
            factor=width/sum(widths);widths=[w*factor for w in widths]
            table=Table([[Paragraph(inline(c),styles['Small']) for c in row] for row in rows],colWidths=widths,repeatRows=1,hAlign='LEFT')
            table.setStyle(TableStyle([('VALIGN',(0,0),(-1,-1),'TOP'),('BACKGROUND',(0,0),(-1,0),colors.HexColor('#e8edf2')),
                ('GRID',(0,0),(-1,-1),0.3,colors.HexColor('#c6ccd2')),('LEFTPADDING',(0,0),(-1,-1),4),
                ('RIGHTPADDING',(0,0),(-1,-1),4),('TOPPADDING',(0,0),(-1,-1),4),('BOTTOMPADDING',(0,0),(-1,-1),4)]))
            story+=[table,Spacer(1,9)];continue
        paragraph=[line];i+=1
        while i<len(lines) and lines[i].strip() and not lines[i].lstrip().startswith(('#','```','|','![')):
            paragraph.append(lines[i].strip());i+=1
        para(' '.join(paragraph))
    doc.multiBuild(story)

if __name__=='__main__':
    markdown=make_markdown();render_pdf(markdown)
    from pypdf import PdfReader
    print('Report generated:',len(PdfReader(REPORT/'Assignment2_Report.pdf').pages),'pages')
