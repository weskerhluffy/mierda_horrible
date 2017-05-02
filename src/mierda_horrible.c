/*
 ============================================================================
 Name        : mierda_horrible.c
 Author      : ernesto
 Version     :
 Copyright   : a veces siento que
 Description : Hello World in C, Ansi-style
 ============================================================================
 XXX: http://www.spoj.com/problems/HORRIBLE/
 XXX: http://zobayer.blogspot.mx/2013/11/various-usage-of-bit.html
 */

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <assert.h>
#include <stddef.h>
#include <unistd.h>
#include <sys/time.h>
#include <math.h>

#ifdef CACA_COMUN_LOG
#include <execinfo.h>
#endif

#ifdef __MACH__
#include <mach/clock.h>
#include <mach/mach.h>
#else
#include <time.h>
#include <stdarg.h>
#endif

#define CACA_COMUN_TAM_MAX_LINEA 200
#define CACA_LOG_MAX_TAM_CADENA 2000

#define CACA_COMUN_BUF_STATICO (char[1000] ) { '\0' }

#define BITCH_VECTOR_NUM_BITS (sizeof(bitch_vector) * 8)

#define CACA_COMUN_ASSERT_DUROTE 0
#define CACA_COMUN_ASSERT_SUAVECITO 1
#define CACA_COMUN_ASSERT_NIMADRES 2

typedef unsigned int natural;
typedef unsigned long long tipo_dato;

typedef long long bitch_vector;

typedef enum BOOLEANOS {
	falso = 0, verdadero
} bool;

/*
 #define CACA_COMUN_TIPO_ASSERT CACA_COMUN_ASSERT_SUAVECITO
 */
#define CACA_COMUN_TIPO_ASSERT CACA_COMUN_ASSERT_DUROTE

#define assert_timeout_dummy(condition) 0;
static inline void caca_log_debug_dummy(const char *format, ...) {
}

#if CACA_COMUN_TIPO_ASSERT == CACA_COMUN_ASSERT_DUROTE
#define assert_timeout(condition) assert(condition);
#endif
#if CACA_COMUN_TIPO_ASSERT == CACA_COMUN_ASSERT_SUAVECITO
#define assert_timeout(condition) if(!(condition)){sleep(10);abort();}
#endif
#if CACA_COMUN_TIPO_ASSERT == CACA_COMUN_ASSERT_NIMADRES
#define assert_timeout(condition) 0
#endif

#ifdef CACA_COMUN_LOG
#define caca_log_debug(formato, args...) \
		do \
		{ \
			size_t profundidad = 0; \
			void *array[CACA_LOG_MAX_TAM_CADENA]; \
 			profundidad = backtrace(array, CACA_LOG_MAX_TAM_CADENA); \
			caca_log_debug_func(formato,__FILE__, __func__, __LINE__,profundidad,##args); \
		} \
		while(0);
#else
#define caca_log_debug caca_log_debug_dummy
#endif

#define caca_comun_max(x,y) ((x) < (y) ? (y) : (x))
#define caca_comun_min(x,y) ((x) < (y) ? (x) : (y))

void caca_log_debug_func(const char *format, ...);

#define caca_comun_mapa_bitch_checa(bits, posicion, resultado) \
        __asm__ (\
                        "xor %%rdx,%%rdx\n"\
                        "movq %[bitch_posi],%%rax\n" \
                        "movq $64,%%r8\n"\
                        "divq %%r8\n"\
                        "mov $1,%[resul]\n"\
                        "mov %%rdx,%%rcx\n"\
                        "shlq %%cl,%[resul]\n"\
                        "and (%[vectors],%%rax,8),%[resul]\n"\
                        : [resul] "=b" (resultado)\
                        : [bitch_posi] "r" (posicion), [vectors] "r" (bits)\
            :"rax","rdx","rcx","r8")

static inline void caca_comun_mapa_bitch_asigna(bitch_vector *bits,
		unsigned long posicion) {
	int idx_arreglo = 0;
	int idx_registro = 0;

	idx_arreglo = posicion / 64;
	idx_registro = posicion % 64;

	bits[idx_arreglo] |= (bitch_vector) ((bitch_vector) 1 << idx_registro);

}

static inline void caca_comun_mapa_bitch_limpia(bitch_vector *bits,
		unsigned long posicion) {
	int idx_arreglo = 0;
	int idx_registro = 0;

	idx_arreglo = posicion / 64;
	idx_registro = posicion % 64;

	bits[idx_arreglo] &= (bitch_vector) ~((bitch_vector) 1 << idx_registro);

}

void caca_comun_current_utc_time(struct timespec *ts) {

#ifdef __MACH__
	clock_serv_t cclock;
	mach_timespec_t mts;
	host_get_clock_service(mach_host_self(), CALENDAR_CLOCK, &cclock);
	clock_get_time(cclock, &mts);
	mach_port_deallocate(mach_task_self(), cclock);
	ts->tv_sec = mts.tv_sec;
	ts->tv_nsec = mts.tv_nsec;
#else
#ifdef CACA_COMUN_LOG
	clock_gettime(CLOCK_REALTIME, ts);
#endif
#endif

}

void caca_comun_timestamp(char *stime) {
	time_t ltime;
	struct tm result;
	long ms;
	struct timespec spec;
	char parte_milisecundos[50];

	ltime = time(NULL );

#ifndef ONLINE_JUDGE
	localtime_r(&ltime, &result);
	asctime_r(&result, stime);
#endif

	*(stime + strlen(stime) - 1) = ' ';

	caca_comun_current_utc_time(&spec);
#ifndef ONLINE_JUDGE
	ms = round(spec.tv_nsec / 1.0e3);
#endif
	sprintf(parte_milisecundos, "%ld", ms);
	strcat(stime, parte_milisecundos);
}
void caca_log_debug_func(const char *format, ...) {

	va_list arg;
	va_list arg2;
	const char *PEDAZO_TIMESTAMP_HEADER = "tiempo: %s; ";
	const char *HEADER =
			"archivo: %s; funcion: %s; linea %d; nivel: %zd caca 8====D ";
	char formato[CACA_LOG_MAX_TAM_CADENA + sizeof(HEADER)
			+ sizeof(PEDAZO_TIMESTAMP_HEADER)] = { '\0' };
	char pedazo_timestamp[sizeof(PEDAZO_TIMESTAMP_HEADER) + 100] = { '\0' };
	char cadena_timestamp[100] = { '\0' };

	caca_comun_timestamp(cadena_timestamp);
	sprintf(pedazo_timestamp, PEDAZO_TIMESTAMP_HEADER, cadena_timestamp);

	strcpy(formato, pedazo_timestamp);
	strcat(formato, HEADER);
	strcat(formato, format);
	strcat(formato, "\n");

	va_start(arg, format);
	va_copy(arg2, arg);
	vprintf(formato, arg2);
	va_end(arg2);
	va_end(arg);
// XXX: http://stackoverflow.com/questions/1716296/why-does-printf-not-flush-after-the-call-unless-a-newline-is-in-the-format-strin
	setbuf(stdout, NULL );
}

#ifdef CACA_COMUN_LOG
static char *caca_comun_arreglo_a_cadena(tipo_dato *arreglo, int tam_arreglo,
		char *buffer) {
	int i;
	char *ap_buffer = NULL;
	int characteres_escritos = 0;
#ifdef ONLINE_JUDGE
	return NULL;
#endif

	memset(buffer, 0, 100);
	ap_buffer = buffer;

	for (i = 0; i < tam_arreglo; i++) {
		characteres_escritos += sprintf(ap_buffer + characteres_escritos,
				"%2llu", *(arreglo + i));
		if (i < tam_arreglo - 1) {
			*(ap_buffer + characteres_escritos++) = ',';
		}
	}
	*(ap_buffer + characteres_escritos) = '\0';
	return ap_buffer;
}

static char *caca_comun_arreglo_a_cadena_natural(natural *arreglo,
		natural tam_arreglo, char *buffer) {
	int i;
	char *ap_buffer = NULL;
	int characteres_escritos = 0;
#ifdef ONLINE_JUDGE
	return NULL;
#endif

	memset(buffer, 0, 100);
	ap_buffer = buffer;

	for (i = 0; i < tam_arreglo; i++) {
		characteres_escritos += sprintf(ap_buffer + characteres_escritos, "%2u",
				*(arreglo + i));
		if (i < tam_arreglo - 1) {
			*(ap_buffer + characteres_escritos++) = ',';
		}
	}
	*(ap_buffer + characteres_escritos) = '\0';
	return ap_buffer;
}
#endif
void caca_comun_strreplace(char s[], char chr, char repl_chr) {
	int i = 0;
	while (s[i] != '\0') {
		if (s[i] == chr) {
			s[i] = repl_chr;
		}
		i++;
	}
}

static inline int caca_comun_lee_matrix_long_stdin(tipo_dato *matrix,
		int *num_filas, int *num_columnas, int num_max_filas,
		int num_max_columnas) {
	int indice_filas = 0;
	int indice_columnas = 0;
	tipo_dato numero = 0;
	char *siguiente_cadena_numero = NULL;
	char *cadena_numero_actual = NULL;
	char *linea = NULL;

	linea = calloc(CACA_COMUN_TAM_MAX_LINEA, sizeof(char));

	while (indice_filas < num_max_filas
			&& fgets(linea, CACA_COMUN_TAM_MAX_LINEA, stdin)) {
		indice_columnas = 0;
		cadena_numero_actual = linea;
		caca_comun_strreplace(linea, '\n', '\0');
		if (!strlen(linea)) {
			caca_log_debug("weird, linea vacia");
			continue;
		}
		for (siguiente_cadena_numero = linea;; siguiente_cadena_numero =
				cadena_numero_actual) {
			caca_log_debug("el numero raw %s", linea);
			numero = strtol(siguiente_cadena_numero, &cadena_numero_actual, 10);
			if (cadena_numero_actual == siguiente_cadena_numero) {
				break;
			}
			*(matrix + indice_filas * num_max_columnas + indice_columnas) =
					numero;
			caca_log_debug("en col %d, fil %d, el valor %lu", indice_columnas,
					indice_filas, numero);
			indice_columnas++;
			caca_log_debug("las columnas son %d", indice_columnas);
		}
		if (num_columnas) {
			num_columnas[indice_filas] = indice_columnas;
		}
		indice_filas++;
		caca_log_debug("las filas son %d, con clos %d", indice_filas,
				indice_columnas);
	}

	*num_filas = indice_filas;
	free(linea);
	return 0;
}

#define MIERDA_HORRIBLE_MAX_NUMS ((natural)1E5)

#if 1

#define BIT_CH_VALOR_INVALIDO ULLONG_MAX
#define BIT_CH_MAX_NODOS MIERDA_HORRIBLE_MAX_NUMS

typedef struct bit_ch {
	natural num_nodos_bit_ch;
	tipo_dato nodos_bit_ch[BIT_CH_MAX_NODOS + 2];
} bit_ch;

static inline void bit_ch_aumenta(bit_ch *bit, tipo_dato nuevo_valor,
		natural idx);

static inline void bit_ch_init(bit_ch *bit, tipo_dato valor_inicial,
		natural num_cacas) {
	tipo_dato *nodos = bit->nodos_bit_ch;

	nodos[0] = BIT_CH_VALOR_INVALIDO;
	for (natural i = 1; i < BIT_CH_MAX_NODOS ; i++) {
		nodos[i] = 0;
	}
	bit->num_nodos_bit_ch = num_cacas;

	bit_ch_aumenta(bit, valor_inicial, 1);
}

static inline void bit_ch_aumenta(bit_ch *bit, tipo_dato nuevo_valor,
		natural idx) {
	tipo_dato *nodos = bit->nodos_bit_ch;
	caca_log_debug("q verga actualizando %u con %lld", idx, nuevo_valor);
	for (natural i = idx; i <= bit->num_nodos_bit_ch; i += (i & (-i))) {
		caca_log_debug("actualizando caca %u con %lld antes %lld", i,
				nuevo_valor, nodos[i]);
		nodos[i] += nuevo_valor;
		caca_log_debug("actualizado caca %u aora %lld", i, nodos[i]);
	}
}

static inline tipo_dato bit_ch_consulta(bit_ch *bit, natural idx) {
	tipo_dato *nodos = bit->nodos_bit_ch;
	tipo_dato res = 0;
	for (int i = idx; i > 0; i -= (i & (-i))) {
		caca_log_debug("consultando caca %u tiene %lld", i, nodos[i]);
		res += nodos[i];
	}
	caca_log_debug("regresando %lld", res);
	return res;
}

static inline void bit_ch_aumenta_rango(bit_ch *bit, tipo_dato nuevo_valor,
		natural idx_ini, natural idx_fin) {
	caca_log_debug("aumentando de %u a %u con valor %lld", idx_ini, idx_fin,
			nuevo_valor);

	bit_ch_aumenta(bit, nuevo_valor, idx_ini);
	bit_ch_aumenta(bit, -nuevo_valor, idx_fin + 1);
}

static inline void bit_ch_aumenta_rango_consulta_rango(bit_ch *bit_puto,
		bit_ch *bit_aux, natural idx_ini, natural idx_fin,
		tipo_dato nuevo_valor) {

	caca_log_debug("aumentando de %u a %u con valor %lld para consulta rango",
			idx_ini, idx_fin, nuevo_valor);

	bit_ch_aumenta_rango(bit_puto, nuevo_valor, idx_ini, idx_fin);
	caca_log_debug(
			"actualizando para consulta rango inicial %d con %lld (%lld * %u)",
			idx_ini, nuevo_valor * (idx_ini - 1), nuevo_valor, idx_ini - 1);
	bit_ch_aumenta(bit_aux, nuevo_valor * (idx_ini - 1), idx_ini);
	caca_log_debug(
			"actualizando para consulta rango final %d con %lld(%lld,%u)",
			idx_fin + 1, -nuevo_valor * idx_fin, -nuevo_valor, idx_fin);
	bit_ch_aumenta(bit_aux, -nuevo_valor * idx_fin, idx_fin + 1);
}

static inline tipo_dato bit_ch_consulta_rango_actualizado_rango(
		bit_ch *bit_puto, bit_ch *bit_aux, natural idx) {
	tipo_dato resul = 0;
	tipo_dato valor_puto = 0;
	tipo_dato valor_aux = 0;

	valor_puto = bit_ch_consulta(bit_puto, idx);

	caca_log_debug("el valor putual en %u es %lld, aportara %lld (%lld * %u)",
			idx, valor_puto, valor_puto * idx, valor_puto, idx);

	valor_aux = bit_ch_consulta(bit_aux, idx);

	caca_log_debug("el valor aux en %u es %lld", idx, valor_puto);

	resul = valor_puto * idx - valor_aux;

	caca_log_debug("la suma acumulacaca hasta %u es %lld", idx, resul);

	return resul;
}

static inline tipo_dato bit_ch_consulta_rango(bit_ch *bit_puto, bit_ch *bit_aux,
		natural idx_ini, natural idx_fin) {
	tipo_dato resul = 0;
	tipo_dato resul_idx_ini = 0;
	tipo_dato resul_idx_fin = 0;

	resul_idx_ini = bit_ch_consulta_rango_actualizado_rango(bit_puto, bit_aux,
			idx_ini - 1);
	caca_log_debug("la suma acumulacaca ini hasta %u es %lld", idx_ini,
			resul_idx_ini);

	resul_idx_fin = bit_ch_consulta_rango_actualizado_rango(bit_puto, bit_aux,
			idx_fin);
	caca_log_debug("la suma acumulacaca fin hasta %u es %lld", idx_fin,
			resul_idx_fin);

	resul = resul_idx_fin - resul_idx_ini;

	caca_log_debug("la suma acumulacaca del rango %u-%u es %lld", idx_ini,
			idx_fin, resul);

	return resul;
}

#endif

bit_ch *bit_puto = &(bit_ch ) { 0 };
bit_ch *bit_aux = &(bit_ch ) { 0 };

tipo_dato consultas[100000][4] = { 0 };

static inline void mierda_horrible_core(natural num_numeros,
		tipo_dato *consultas, natural num_consultas) {
	memset(bit_puto, 0, sizeof(bit_ch));
	memset(bit_aux, 0, sizeof(bit_ch));

	bit_ch_init(bit_puto, 0, num_numeros);
	bit_ch_init(bit_aux, 0, num_numeros);

	for (int i = 0; i < num_consultas; i++) {
		tipo_dato *consulta_act = (consultas + i * 4);
		tipo_dato tipo_consulta = 0;

		tipo_consulta = consulta_act[0];
		caca_log_debug("la consulta %u es tipo %lld", i, tipo_consulta);
		natural idx_ini = consulta_act[1];
		natural idx_fin = consulta_act[2];

		caca_log_debug("el intervalo de la operacion %u-%u", idx_ini, idx_fin);

		if (!tipo_consulta) {
			tipo_dato nuevo_valor = consulta_act[3];
			caca_log_debug("actualizando con valor %lld", nuevo_valor);
			bit_ch_aumenta_rango_consulta_rango(bit_puto, bit_aux, idx_ini,
					idx_fin, nuevo_valor);
		} else {
			tipo_dato res = 0;
			caca_log_debug("aciendo consulta");
			res = bit_ch_consulta_rango(bit_puto, bit_aux, idx_ini, idx_fin);
			caca_log_debug("resultado %lld", res);
		}
	}
}

static inline void mierda_horrible_main() {
	natural num_cacasos = 0;

	scanf("%u", &num_cacasos);

	for (int i = 0; i < num_cacasos; i++) {
		natural num_numeros = 0;
		natural num_comsultas = 0;
		scanf("%u %u", &num_numeros, &num_comsultas);
		caca_comun_lee_matrix_long_stdin((tipo_dato *) consultas, &(int ) { 0 },
				NULL, 100000, 4);

		mierda_horrible_core(num_numeros, (tipo_dato*) consultas,
				num_comsultas);
	}
}

int main(void) {
	mierda_horrible_main();
	return EXIT_SUCCESS;
}
