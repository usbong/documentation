/*
 * Copyright 2018~2021 USBONG SOCIAL SYSTEMS, INC. (USBONG)
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *     http://www.apache.org/licenses/LICENSE-2.0
 *     
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * @company: USBONG SOCIAL SYSTEMS, INC. (USBONG)
 * @author: SYSON, MICHAEL B.
 * @date created: 2018
 * @last updated: 20210418
 * @website: http://www.usbong.ph
 *
 * Reference:
 * http://www.opengl-tutorial.org/beginners-tutorials/tutorial-7-model-loading/;
 * last accessed: 20210328
 * 
 * Acknowledgments:
 * 1) "Bulalakaw Wars" Team (2007): 
 * Syson, M., Camacho, R., Gonzales, D., Del Rosario, R., Vidal, E., et al.
 *
 * 2) Marikina Orthopedic Specialty Clinic (MOSC)
 * 
 * 3) Sta. Lucia Health Care Center (SLHCC)
 *
 */

//TO-DO: -update: this 
/*
// example output:
	glBegin(GL_QUADS);
		glNormal3f(0.203681, 0.975646, -0.081118);
		glTexCoord2f(0.796491, 0.833459);
		glVertex3f(0.421715, 1.200705, -0.286078);
		glNormal3f(0.126469, 0.987487, -0.093905);
		glTexCoord2f(0.808374, 0.835839);
		glVertex3f(0.282711, 1.220871, -0.272377);
		glNormal3f(0.229011, 0.973388, 0.001648);
		glTexCoord2f(0.816882, 0.846686);
		glVertex3f(0.300318, 1.233293, 0.006505);
		glNormal3f(0.287545, 0.957030, 0.037080);
		glTexCoord2f(0.800921, 0.841661);
		glVertex3f(0.488887, 1.186340, -0.116857);
	glEnd();
*/

 
import java.util.*;
import java.io.File;
import java.io.FileInputStream;
import java.io.PrintWriter;
import java.util.regex.Pattern;
import java.util.regex.Matcher;
import java.text.NumberFormat;
import java.text.DecimalFormat;
//import java.lang.Integer;

/*
' Given:
' 1) .obj file exported from Blender 3D Tool
'
' Output:
' 1) .txt file with the auto-generated set of instructions 
' 	   to be executed using OpenGL (Graphics Library)
'
' Notes:
' 1) To execute the add-on software/application simply use the following command:
'   java generateOpenGLInstructionsFromBlenderOBJFile *.obj
' 
' reminder: verify that at least 1 .obj file exists inside the input folder
' 
*/ 

public class generateOpenGLInstructionsFromBlenderOBJFile {	
	private static boolean inDebugMode = true;
	private static String inputFilename = "input202103"; //without extension; default input file
	
	//added by Mike, 20210328
	private static Vector<String[]> vVertexContainerTemp;
	private static Vector<String[]> vNormalContainerTemp;
	private static Vector<String[]> vTextureCoordinatesContainerTemp;
	
	private static Vector<String> vVertexIndicesContainer;
	private static Vector<String> vNormalIndicesContainer;
	private static Vector<String> vTextureCoordinatesIndicesContainer;

	private static Vector<String[]> vVertexContainerOutput;
	private static Vector<String[]> vNormalContainerOutput;
	private static Vector<String[]> vTextureCoordinatesContainerOutput;	
	
	private static String medicalDoctorInput = ""; //added by Mike, 20200216
	private static PrintWriter consultationWriter; //added by Mike, 20200217
	
	private static boolean hasProcessedPTTreatment = false; //added by Mike, 20200217
	
	private static String startDate = null;
	private static String endDate = null;
	
	private static final int INPUT_REFERRING_DOCTOR_COLUMN = 15;
	private static final int INPUT_NOTES_COLUMN = 0;
	private static final int INPUT_DATE_COLUMN = 1;
	private static final int INPUT_NAME_COLUMN = 3;
	private static final int INPUT_CLASS_COLUMN = 8; //HMO and NON-HMO
	private static final int INPUT_FEE_COLUMN = 7; //added by Mike, 20190119
	private static final int INPUT_CONSULTATION_FEE_COLUMN = 8; //added by Mike, 20190119
	private static final int INPUT_NET_PF_COLUMN = 10;
	private static final int INPUT_NEW_OLD_COLUMN = 16;
	private static final int INPUT_APPROVAL_CODE_COLUMN = 12; //added by Mike, 20190119

	private static final int INPUT_CONSULTATION_PROCEDURE_COLUMN = 2;
	//added by Mike, 20190107
	private static final int INPUT_CONSULTATION_MEDICAL_CERTIFICATE_COLUMN = 2; //The int value is the same as "INPUT_CONSULTATION_PROCEDURE_COLUMN".
	private static final int INPUT_CONSULTATION_MEDICAL_DOCTOR_COLUMN = 16; //added by Mike, 20190122

	//added by Mike, 20181218
	//CONSULTATION
/*	
	private static final int INPUT_CONSULTATION_CLASS_COLUMN = 9;
	private static final int INPUT_CONSULTATION_NET_PF_COLUMN = 11;
	private static final int INPUT_CONSULTATION_NEW_OLD_COLUMN = 17;
*/	
	private static final int INPUT_CONSULTATION_OFFSET = 1;
		
		
/*	private static HashMap<String, double[]> referringDoctorContainer;	
*/

	private static ArrayList<String[]> transactionDateContainer;	//added by Mike, 20190119

	private static HashMap<Integer, double[]> dateContainer;	//added by Mike, 201801205
	private static HashMap<String, double[]> hmoContainer;	//added by Mike, 201801217
	private static HashMap<String, double[]> nonHmoContainer;	//added by Mike, 201801217
	private static HashMap<String, double[]> referringDoctorContainer; //added by Mike, 20181218

	private static String[] columnValuesStringArray; //added by Mike, 20190119
	
	private static double[] columnValuesArray;
	private static String[] dateValuesArray; //added by Mike, 20180412
	private static int[] dateValuesArrayInt; //added by Mike, 20181206
	//private static ArrayList<int> dateValuesArrayInt; //edited by Mike, 20181221
		
	//the date and the referring doctor are not yet included here
	//this is for both HMO and NON-HMO transactions
	private static final int OUTPUT_TOTAL_COLUMNS = 23; //edited by Mike, 20190107

	//PT TREATMENT
	private static final int OUTPUT_HMO_COUNT_COLUMN = 0; //transaction count
	private static final int OUTPUT_HMO_TOTAL_NET_TREATMENT_FEE_COLUMN = 1;
	private static final int OUTPUT_HMO_PAID_NET_TREATMENT_FEE_COLUMN = 2;
	private static final int OUTPUT_HMO_UNPAID_NET_TREATMENT_FEE_COLUMN = 3;
	private static final int OUTPUT_HMO_NEW_OLD_COUNT_COLUMN = 4;

	private static final int OUTPUT_NON_HMO_COUNT_COLUMN = 5; //transaction count
	private static final int OUTPUT_NON_HMO_TOTAL_NET_TREATMENT_FEE_COLUMN = 6;
	private static final int OUTPUT_NON_HMO_PAID_NET_TREATMENT_FEE_COLUMN = 7;
	private static final int OUTPUT_NON_HMO_UNPAID_NET_TREATMENT_FEE_COLUMN = 8;
	private static final int OUTPUT_NON_HMO_NEW_OLD_COUNT_COLUMN = 9;
	
	private static final int OUTPUT_DATE_ID_COLUMN = 10; //added by Mike, 20181205
	
	//CONSULTATION
	private static final int OUTPUT_CONSULTATION_HMO_COUNT_COLUMN = 11; //transaction count
	private static final int OUTPUT_CONSULTATION_NON_HMO_COUNT_COLUMN = 12; //transaction count
	private static final int OUTPUT_CONSULTATION_HMO_PROCEDURE_COUNT_COLUMN = 13; //transaction count
	private static final int OUTPUT_CONSULTATION_NON_HMO_PROCEDURE_COUNT_COLUMN = 14; //transaction count
	private static final int OUTPUT_CONSULTATION_HMO_MEDICAL_CERTIFICATE_COUNT_COLUMN = 15; //transaction count; added by Mike, 20190107
	private static final int OUTPUT_CONSULTATION_NON_HMO_MEDICAL_CERTIFICATE_COUNT_COLUMN = 16; //transaction count; added by Mike, 20190107

	//added by Mike, 20190119
	private static final int OUTPUT_HMO_FEE_COLUMN = 17;
	private static final int OUTPUT_HMO_APPROVAL_CODE_COLUMN = 18;
	private static final int OUTPUT_HMO_NAME_COLUMN = 19;
	private static final int OUTPUT_HMO_CLASS_COLUMN = 20;
	private static final int OUTPUT_HMO_FILE_TYPE_COLUMN = 21; //Consultation or PT Treatment?
	private static final int OUTPUT_HMO_DATE_COLUMN = 22;

	private static boolean isConsultation;
	
	private static DecimalFormat df = new DecimalFormat("0.00"); //added by Mike, 20181105
	private static int rowCount; //added by Mike, 20181105
				
	private static int totalCountForAllReferringDoctors;
	private static double totalNetTreatmentFeeForAllReferringDoctors;
	private static double totalPaidNetTreatmentFeeForAllReferringDoctors;
	private static double totalUnpaidNetTreatmentFeeForAllReferringDoctors;
	private static double totalFivePercentShareOfNetPaidForAllReferringDoctors;
				
	//added by Mike, 20181220
	private static HashMap<String, HashMap<String, double[]>> classificationContainerPerMedicalDoctor = new HashMap<String, HashMap<String, double[]>>();
	private static HashMap<String, double[]> classificationContainerHashmap = new HashMap<String, double[]>();
	private static double[] classificationContainerColumnValuesArray = new double[OUTPUT_TOTAL_COLUMNS];
	private static boolean hasSetClassificationContainerPerMedicalDoctor=false;
	
	public static void main ( String[] args ) throws Exception
	{					
		makeFilePath("output"); //"output" is the folder where I've instructed the add-on software/application to store the output file			
		
		PrintWriter outputWriter = new PrintWriter("output/openGLInstructions.txt", "UTF-8");			

		//added by Mike, 20181116
		startDate = null; //properly set the month and year in the output file of each input file
		dateValuesArray = new String[args.length]; //added by Mike, 20180412
		dateValuesArrayInt = new int[args.length]; //added by Mike, 20180412
		//dateValuesArrayInt = new ArrayList<int>(); //edited by Mike, 20181221

		processInputFiles(args, true);	

		//TO-DO: -reverify: output
		//OUTPUT		
		//edited by Mike, 20210403; edited by Mike, 20210412
//		outputWriter.print("glBegin(GL_QUADS);\n");
		outputWriter.print("glBegin(GL_TRIANGLES);\n");
		
	    int iVertexContainerOutputSize = vVertexContainerOutput.size();
	    int iTextureCoordinatesContainerOutputSize = vTextureCoordinatesContainerOutput.size();
	    int iNormalContainerOutputSize = vNormalContainerOutput.size();		
		
		//note: size of all Output containers equal
/*		
		System.out.println("iVertexContainerOutputSize: " + iVertexContainerOutputSize);
		System.out.println("iTextureCoordinatesContainerOutputSize: " + iTextureCoordinatesContainerOutputSize);
		System.out.println("iNormalContainerOutputSize: " + iNormalContainerOutputSize);
*/		

		//added by Mike, 20210415
		int iTriangleCount=1;
		int iVertexCount=0;
		
		for (int iCount=0; iCount<iVertexContainerOutputSize; iCount++) {
			String[] sbNormalArray = vNormalContainerOutput.get(iCount);
			String[] sbTextureCoordinatesArray = vTextureCoordinatesContainerOutput.get(iCount);
			String[] sbVertexArray = vVertexContainerOutput.get(iCount);
			
			//added by Mike, 20210415
			if (iVertexCount==0) {
				//edited by Mike, 20210418
//				outputWriter.print("\tTriangle#"+iTriangleCount+"-----\n");
				outputWriter.print("\t//Triangle#"+iTriangleCount+"-----\n");
				
				iTriangleCount=iTriangleCount+1;				
				iVertexCount=iVertexCount+1;
			}
			else {
				if (iVertexCount<2) { //0 included in count as 1
					iVertexCount=iVertexCount+1;				
				}
				else {
					iVertexCount=0;
				}
			}
			
			
			//edited by Mike, 20210329
			//output example: glNormal3f(0.203681, 0.975646, -0.081118);
			outputWriter.print("\tglNormal3f("+sbNormalArray[0]+","+sbNormalArray[1]+","+sbNormalArray[2]+");\n");

			//output example: glTexCoord2f(0.796491, 0.833459);
			outputWriter.print("\tglTexCoord2f("+sbTextureCoordinatesArray[0]+","+sbTextureCoordinatesArray[1]+");\n");
			
			//output example: glVertex3f(0.421715, 1.200705, -0.286078);
			outputWriter.print("\tglVertex3f("+sbVertexArray[0]+","+sbVertexArray[1]+","+sbVertexArray[2]+");\n");			
						
			//output example: glVertex3f(0.421715, 1.200705, -0.286078);
			//edited by Mike, 20210329
//			outputWriter.print("\tglVertex3f("+sbVertexArray[0]+","+sbVertexArray[1]+","+sbVertexArray[2]+");\n");
			
			//added by Mike, 20210415
			if (iCount+1<iVertexContainerOutputSize) {
				outputWriter.print("\n");			
			}
		}

		outputWriter.print("glEnd();\n");
		outputWriter.close();
		
/*
		//added by Mike, 20200217		
		//medicalDoctorInput = "CIELO"; //added by Mike, 20200216

		File medicalDoctorInputFile = new File("assets/MedicalDoctorList.txt");
		
		Scanner sc = new Scanner(new FileInputStream(medicalDoctorInputFile));				
	
		//medicalDoctorInput=sc.nextLine(); //skip the first row, which is the input file's table headers
				
		//count/compute the number-based values of inputColumns 
		while (sc.hasNextLine()) {
			medicalDoctorInput=sc.nextLine();
		
			consultationWriter = new PrintWriter("output/UnpaidHMOSummaryReportOutputConsultation" + medicalDoctorInput+".txt", "UTF-8");			
			
			transactionDateContainer = new ArrayList<String[]>();
			
			//PART/COMPONENT/MODULE/PHASE 1
			processInputFiles(args, true);	
			
			//OUTPUT
			//added by Mike, 20181118
			consultationWriter.print("Unpaid HMO Summary Report (CONSULTATION)\n");
			
			//--------------------------------------------------------------------
			//added by Mike, 20190122
			double totalUnpaidHMOFeeConsultation = 0;
//			double totalUnpaidHMOFeeTreatment = 0;
			
			//init table header names
	//		writer.print("CONSULTATION\n");
			consultationWriter.print("DATE:\tPATIENT NAME:\tFEE:\tCLASSIFICATION:\tAPPROVAL CODE:\tUNPAID REASON:\n"); 		
			for(int i=0; i<transactionDateContainer.size(); i++) {
				if (transactionDateContainer.get(i)[OUTPUT_HMO_FILE_TYPE_COLUMN].toLowerCase().trim().equals("consultation")){
					consultationWriter.print(
									transactionDateContainer.get(i)[OUTPUT_HMO_DATE_COLUMN]+"\t"+
									transactionDateContainer.get(i)[OUTPUT_HMO_NAME_COLUMN]+"\t"+
									transactionDateContainer.get(i)[OUTPUT_HMO_FEE_COLUMN]+"\t"+
									transactionDateContainer.get(i)[OUTPUT_HMO_CLASS_COLUMN]+"\t"+
	//								transactionDateContainer.get(i)[OUTPUT_HMO_APPROVAL_CODE_COLUMN]+"\n"
									"\t\n"
								); 				   											
								
					//added by Mike, 20190122
					totalUnpaidHMOFeeConsultation += Double.parseDouble(transactionDateContainer.get(i)[OUTPUT_HMO_FEE_COLUMN].replace("\"","").replace(",",""));
				}
			}
			consultationWriter.print("TOTAL:\t\t"+totalUnpaidHMOFeeConsultation+"\n"); 					
			consultationWriter.close();		

			//added by Mike, 20200217
			if (medicalDoctorInput.equals("PEDRO")) {
				double totalUnpaidHMOFeeTreatment = 0;

				treatmentWriter.print("Unpaid HMO Summary Report (PT TREATMENT)\n");

		//		treatmentWriter.print("\nPT TREATMENT\n");
				treatmentWriter.print("DATE:\tPATIENT NAME:\tFEE:\tCLASSIFICATION:\tAPPROVAL CODE:\tUNPAID REASON:\n"); 		
				for(int i=0; i<transactionDateContainer.size(); i++) {
					if (transactionDateContainer.get(i)[OUTPUT_HMO_FILE_TYPE_COLUMN].toLowerCase().trim().equals("treatment")){
						treatmentWriter.print(
										transactionDateContainer.get(i)[OUTPUT_HMO_DATE_COLUMN]+"\t"+
										transactionDateContainer.get(i)[OUTPUT_HMO_NAME_COLUMN]+"\t"+
										transactionDateContainer.get(i)[OUTPUT_HMO_FEE_COLUMN]+"\t"+
										transactionDateContainer.get(i)[OUTPUT_HMO_CLASS_COLUMN]+"\t"+
										transactionDateContainer.get(i)[OUTPUT_HMO_APPROVAL_CODE_COLUMN]+"\n"
									); 				   											
									
						//added by Mike, 20190122
						totalUnpaidHMOFeeTreatment += Double.parseDouble(transactionDateContainer.get(i)[OUTPUT_HMO_FEE_COLUMN].replace("\"","").replace(",",""));
					}
				}
				treatmentWriter.print("TOTAL:\t\t"+totalUnpaidHMOFeeTreatment+"\n"); 		
				
		//		consultationWriter.close();		//removed by Mike, 20200217
				treatmentWriter.close();
			}
		}
*/		
	}
	
	private static String convertDateToMonthYearInWords(int date) {
		StringBuffer sb = new StringBuffer(""+date);	
		String year = sb.substring(0,4); //index 4 is not included
		int month = Integer.parseInt(sb.substring(4,6)); //index 6 is not included
		
		switch(month) {
			case 1:
				return "January" + " " + year;
			case 2:
				return "February" + " " + year;
			case 3:
				return "March" + " " + year;
			case 4:
				return "April" + " " + year;
			case 5:
				return "May" + " " + year;
			case 6:
				return "June" + " " + year;
			case 7:
				return "July" + " " + year;
			case 8:
				return "August" + " " + year;
			case 9:
				return "September" + " " + year;
			case 10:
				return "October" + " " + year;
			case 11:
				return "November" + " " + year;
			case 12:
				return "December" + " " + year;
		}	

		return null;//error
	}
	
	private static String getMonthYear(String date) {
		StringBuffer sb = new StringBuffer(date);				
		return sb.substring(0,3).concat("-").concat(sb.substring(sb.length()-2,sb.length()));
	}
	
	//added by Mike, 20181030
	private static void makeFilePath(String filePath) {
		File directory = new File(filePath);		
		if (!directory.exists() && !directory.mkdirs()) 
    	{
    		System.out.println("File Path to file could not be made.");
    	}    			
	}
	
	//added by Mike, 20181216
	private static void processUnpaidHMOCount(ArrayList<String[]> transactionDateContainer, String[] inputColumns, boolean isConsultation) {
		columnValuesStringArray = new String[OUTPUT_TOTAL_COLUMNS];

		columnValuesStringArray[OUTPUT_HMO_DATE_COLUMN] = inputColumns[INPUT_DATE_COLUMN];
		columnValuesStringArray[OUTPUT_HMO_NAME_COLUMN] = inputColumns[INPUT_NAME_COLUMN];
		columnValuesStringArray[OUTPUT_HMO_APPROVAL_CODE_COLUMN] = inputColumns[INPUT_APPROVAL_CODE_COLUMN];

		//edited by Mike, 20181218
		if (!isConsultation) {											
			columnValuesStringArray[OUTPUT_HMO_FILE_TYPE_COLUMN] = "TREATMENT";
			columnValuesStringArray[OUTPUT_HMO_FEE_COLUMN] = inputColumns[INPUT_FEE_COLUMN];
			columnValuesStringArray[OUTPUT_HMO_CLASS_COLUMN] = inputColumns[INPUT_CLASS_COLUMN];

			//edited by Mike, 20181206
			if ((inputColumns[INPUT_CLASS_COLUMN].contains("HMO")) ||
				(inputColumns[INPUT_CLASS_COLUMN].contains("SLR"))) {
				if (!inputColumns[INPUT_NOTES_COLUMN].contains("paid:")) {
					transactionDateContainer.add(columnValuesStringArray);
				}
			}
		}
		else {												
			//added by Mike, 20190122
			//do the set of instructions if the MEDICAL DOCTOR has the keywords "syson" and "pedro"
/*			if ((inputColumns[INPUT_CONSULTATION_MEDICAL_DOCTOR_COLUMN].toLowerCase().trim().contains("syson")) &&
						(inputColumns[INPUT_CONSULTATION_MEDICAL_DOCTOR_COLUMN].toLowerCase().trim().contains("pedro"))) {
*/
if ((inputColumns[INPUT_CONSULTATION_MEDICAL_DOCTOR_COLUMN].toUpperCase().trim().contains(medicalDoctorInput))) {/* &&
						(inputColumns[INPUT_CONSULTATION_MEDICAL_DOCTOR_COLUMN].toLowerCase().trim().contains(medicalDoctorInput))) {
*/
				columnValuesStringArray[OUTPUT_HMO_FILE_TYPE_COLUMN] = "CONSULTATION";
				columnValuesStringArray[OUTPUT_HMO_FEE_COLUMN] = inputColumns[INPUT_CONSULTATION_FEE_COLUMN];
				columnValuesStringArray[OUTPUT_HMO_CLASS_COLUMN] = inputColumns[INPUT_CLASS_COLUMN+INPUT_CONSULTATION_OFFSET];

				if ((inputColumns[INPUT_CLASS_COLUMN+INPUT_CONSULTATION_OFFSET].contains("HMO")) ||
					(inputColumns[INPUT_CLASS_COLUMN+INPUT_CONSULTATION_OFFSET].contains("SLR"))) {
					if (!inputColumns[INPUT_NOTES_COLUMN].contains("paid:")) {
						transactionDateContainer.add(columnValuesStringArray);
					}
				}							
			}					
		}
	}

	private static void processInputFiles(String[] args, boolean isPhaseOne) throws Exception {
		//Vector<String[]> vVertexContainerTemp = new Vector<String[]>();
		vVertexContainerTemp = new Vector<String[]>();
		vTextureCoordinatesContainerTemp = new Vector<String[]>();
		vNormalContainerTemp = new Vector<String[]>();
		
		vVertexIndicesContainer = new Vector<String>();
		vTextureCoordinatesIndicesContainer = new Vector<String>();
		vNormalIndicesContainer = new Vector<String>();

		vVertexContainerOutput = new Vector<String[]>();
		vTextureCoordinatesContainerOutput = new Vector<String[]>();
		vNormalContainerOutput = new Vector<String[]>();
				
		//---------------------------------------------------------------------------
		//part 1		
		for (int i=0; i<args.length; i++) {						
			inputFilename = args[i].replaceAll(".obj","");			
			File f = new File(inputFilename+".obj");

			System.out.println("inputFilename: " + inputFilename);
						
			Scanner sc = new Scanner(new FileInputStream(f));				
		
			String s;		
			//removed by Mike, 20210328
//			s=sc.nextLine(); //skip the first row, which is the input file's table headers
	
			if (inDebugMode) {
				rowCount=0;
			}
						
			//count/compute the number-based values of inputColumns 
			while (sc.hasNextLine()) {
				s=sc.nextLine();

				//we put this here to include all rows in the count
				//start at 1
				if (inDebugMode) {
					rowCount++;
					System.out.println("rowCount: "+rowCount);
				}

				//if the row is blank
				if (s.trim().equals("")) {
					continue;
				}
				
				String[] inputColumns = s.split(" "); //blank space as delimiter

				if (inputColumns[0].equals("#")) {
					continue;
				}
				else if (inputColumns[0].equals("mtllib")) {
					continue;
				}
				else if (inputColumns[0].equals("usemtl")) {
					continue;
				}
				else if (inputColumns[0].equals("o")) {
					//o: object type, e.g. cube
					//TO-DO: -update: this
					continue;
				}
				else if (inputColumns[0].equals("s")) {
					//TO-DO: -update: this
					continue;
				}
				//vertex
				else if (inputColumns[0].equals("v")) {
					String[] sbVertexArray = {inputColumns[1],inputColumns[2],inputColumns[3]};
					vVertexContainerTemp.add(sbVertexArray);
				}
				//vertex texture
				else if (inputColumns[0].equals("vt")) {
					String[] sbTextureCoordinatesArray = {inputColumns[1],inputColumns[2]};
					vTextureCoordinatesContainerTemp.add(sbTextureCoordinatesArray);					
				}
				//vertex normal
				else if (inputColumns[0].equals("vn")) {
					String[] sbNormalArray = {inputColumns[1],inputColumns[2],inputColumns[3]};
					vNormalContainerTemp.add(sbNormalArray);					
				}
				//TO-DO: -reverify: this
				//face; vertex index starts at 1, instead of 0
				else if (inputColumns[0].equals("f")) {
					//we start at iCountInputColumns=1
					//iCountInputColumns[0] is for "f"	
					//three sets delimited by blank space, i.e. " " 
					//we do not include "f"
					for (int iCountInputColumnsSet=1; iCountInputColumnsSet<4; iCountInputColumnsSet++) {					
						//three sets delimited by forward slash, i.e. "/" 
						for (int iCountInputColumns=0; iCountInputColumns<3; iCountInputColumns++) {
							//added by Mike, 20210329
							String[] sbInputColumnsF = inputColumns[iCountInputColumnsSet].split("/");
							
	//						System.out.println("sbInputColumnsF[0]: "+sbInputColumnsF[0]);

							String[] sbIndexArray = {sbInputColumnsF[0],sbInputColumnsF[1],sbInputColumnsF[2]};

							//added by Mike, 20210402
							System.out.println("sbInputColumnsF["+iCountInputColumns+"]: "+sbInputColumnsF[iCountInputColumns]);

							
							//edited by Mike, 20210402
//							if (iCountInputColumns==1) {
							if (iCountInputColumns==0) {								
	//							vVertexIndicesContainer.add(sbIndexArray);
								vVertexIndicesContainer.add(sbIndexArray[0]);
							}
							//edited by Mike, 20210402
//							else if (iCountInputColumns==2) {
							else if (iCountInputColumns==1) {								
	//							vTextureCoordinatesIndicesContainer.add(sbIndexArray);
								vTextureCoordinatesIndicesContainer.add(sbIndexArray[1]);
							}
							else {
	//							vNormalIndicesContainer.add(sbIndexArray);
								vNormalIndicesContainer.add(sbIndexArray[2]);
							}
						}
					}
				}
			}		
		}	
		//---------------------------------------------------------------------------		
		
		//---------------------------------------------------------------------------
		//part 2		
	    int iVertexIndicesContainerSize = vVertexIndicesContainer.size();
	    int iTextureCoordinatesIndicesContainerSize = vTextureCoordinatesIndicesContainer.size();
	    int iNormalIndicesContainerSize = vNormalIndicesContainer.size();
		
		//edited by Mike, 20210403
		//eliminated execss loops classified to be "for"
/*		
	    for (int iCount=0; iCount<iVertexIndicesContainerSize; iCount++) {		 
	    	int iVertexIndex = Integer.parseInt(vVertexIndicesContainer.get(iCount));		   
			//-1 due to .obj file indexing starts at 1, instead of 0
////			System.out.println("iVertexIndex: "+iVertexIndex);
////			System.out.println("vVertexContainerTempSize: "+vVertexContainerTemp.size());
////			System.out.println("vVertexContainerValue: "+vVertexContainerTemp.get(iVertexIndex-1)[0]);
		
			//TO-DO: -add: increment via iCount
			//TO-DO: -get array of f, 3 sets
		 	vVertexContainerOutput.add(vVertexContainerTemp.get(iVertexIndex-1));
		}		

		for (int iCount=0; iCount<iTextureCoordinatesIndicesContainerSize; iCount++) {		 
			//edited by Mike, 20210329
////	    	int iTextureCoordinatesIndex = Integer.parseInt(vTextureCoordinatesIndicesContainer.get(iCount));
////			//-1 due to .obj file indexing starts at 1, instead of 0
////			vTextureCoordinatesContainerOutput.add(vTextureCoordinatesContainerTemp.get(iTextureCoordinatesIndex-1));

			int iTextureCoordinatesIndex;
			//note: select values blank
			if (vTextureCoordinatesIndicesContainer.get(iCount).equals("")) {
				iTextureCoordinatesIndex = 0; 
				//-1 due to .obj file indexing starts at 1, instead of 0
				vTextureCoordinatesContainerOutput.add(vTextureCoordinatesContainerTemp.get(0));
			}
			else {
	    		iTextureCoordinatesIndex = Integer.parseInt(vTextureCoordinatesIndicesContainer.get(iCount));
				//-1 due to .obj file indexing starts at 1, instead of 0
				vTextureCoordinatesContainerOutput.add(vTextureCoordinatesContainerTemp.get(iTextureCoordinatesIndex-1));
			}				
		}		

	    for (int iCount=0; iCount<iNormalIndicesContainerSize; iCount++) {		 
	    	int iNormalIndex = Integer.parseInt(vNormalIndicesContainer.get(iCount));
		   
			//-1 due to .obj file indexing starts at 1, instead of 0
			vNormalContainerOutput.add(vNormalContainerTemp.get(iNormalIndex-1));
		}		
*/		
		//note: index size for all container outputs, e.g. textures, normals,
		//equal with iVertexIndicesContainerSize
	    for (int iCount=0; iCount<iVertexIndicesContainerSize; iCount++) {		 
	    	int iVertexIndex = Integer.parseInt(vVertexIndicesContainer.get(iCount));		   
			//-1 due to .obj file indexing starts at 1, instead of 0
////			System.out.println("iVertexIndex: "+iVertexIndex);
////			System.out.println("vVertexContainerTempSize: "+vVertexContainerTemp.size());
////			System.out.println("vVertexContainerValue: "+vVertexContainerTemp.get(iVertexIndex-1)[0]);
		
			//TO-DO: -add: increment via iCount
			//TO-DO: -get array of f, 3 sets
		 	vVertexContainerOutput.add(vVertexContainerTemp.get(iVertexIndex-1));
			
			int iTextureCoordinatesIndex;
			//note: select values blank
			if (vTextureCoordinatesIndicesContainer.get(iCount).equals("")) {
				iTextureCoordinatesIndex = 0; 
				//-1 due to .obj file indexing starts at 1, instead of 0
				vTextureCoordinatesContainerOutput.add(vTextureCoordinatesContainerTemp.get(0));
			}
			else {
	    		iTextureCoordinatesIndex = Integer.parseInt(vTextureCoordinatesIndicesContainer.get(iCount));
				//-1 due to .obj file indexing starts at 1, instead of 0
				vTextureCoordinatesContainerOutput.add(vTextureCoordinatesContainerTemp.get(iTextureCoordinatesIndex-1));
			}		
			
			int iNormalIndex = Integer.parseInt(vNormalIndicesContainer.get(iCount));
		   
			//-1 due to .obj file indexing starts at 1, instead of 0
			vNormalContainerOutput.add(vNormalContainerTemp.get(iNormalIndex-1));
		}		
		
		//---------------------------------------------------------------------------		
		
	}
	
	//edited by Mike, 20210328
	private static void processInputFilesPrev(String[] args, boolean isPhaseOne) throws Exception {
		//edited by Mike, 20181030
		for (int i=0; i<args.length; i++) {						
			//added by Mike, 20181030
			inputFilename = args[i].replaceAll(".txt","");			
			File f = new File(inputFilename+".txt");

			System.out.println("inputFilename: " + inputFilename);
			
			if (inputFilename.toLowerCase().contains("consultation")) {
				isConsultation=true;
			}
			else {
				isConsultation=false;				

				//added by Mike, 20200217
				if (!medicalDoctorInput.equals("PEDRO")) {					
					continue;
				}
				else {
					System.out.println(">>> " + medicalDoctorInput);
				}
			}
			
			Scanner sc = new Scanner(new FileInputStream(f));				
		
			String s;		
			s=sc.nextLine(); //skip the first row, which is the input file's table headers
	
			if (inDebugMode) {
				rowCount=0;
			}
						
			//count/compute the number-based values of inputColumns 
			while (sc.hasNextLine()) {
				s=sc.nextLine();
				
				//if the row is blank
				if (s.trim().equals("")) {
					continue;
				}
				
				String[] inputColumns = s.split("\t");					
				
				//added by Mike, 20180412
				if (dateValuesArray[i]==null) {
					dateValuesArray[i] = getMonthYear(inputColumns[INPUT_DATE_COLUMN]);
				}

				if (dateValuesArrayInt[i]==0) {
					dateValuesArrayInt[i] = Integer.parseInt(args[i].substring(args[i].indexOf("_")+1,args[i].indexOf(".txt")));
				}
/*
				int dateValueInt = Integer.parseInt(args[i].substring(args[i].indexOf("_")+1,args[i].indexOf(".txt")));
				if (!dateValuesArrayInt.contains(dateValueInt)){
					dateValuesArrayInt.add(dateValueInt);
				}				
*/				
				//edited by Mike, 20181121
				if (startDate==null) {
					startDate = getMonthYear(inputColumns[INPUT_DATE_COLUMN]);
					endDate = startDate;
				}
				else {
					//edited by Mike, 20181121
					//add this condition in case the input file does not have a date for each transaction; however, ideally, for input files 2018 onwards, each transaction should have a date
					if (!inputColumns[INPUT_DATE_COLUMN].trim().equals("")) {
						endDate = getMonthYear(inputColumns[INPUT_DATE_COLUMN]);
					}
				}

				if (inDebugMode) {
					rowCount++;
					System.out.println("rowCount: "+rowCount);
				}
				
				//added by Mike, 20181121
				//skip transactions that have "RehabSupplies" as its "CLASS" value
				//In Excel logbook/workbook 2018 onwards, such transactions are not included in the Consultation and PT Treatment Excel logbooks/workbooks.
				if (inputColumns[INPUT_CLASS_COLUMN].contains("RehabSupplies")) {
					continue;
				}

				if (isPhaseOne) {
					//added by Mike, 20190119
					processUnpaidHMOCount(transactionDateContainer, inputColumns, isConsultation); //isConsultation = false
				}
			}		
		}		
	}
}
