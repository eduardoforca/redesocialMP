/** @file test_redesocial.cpp
 *  @brief Rotina de testes unitários da Rede Social
 *
 *  Testa as funções da biblioteca redesocial.h utilizando o framework
 *  de testes Google Tests
 *  
 *	@author Eduardo Sousa (eduardoforca) Ana Pergentino(AnaPergentino)
 *  @date 4 Jul 2017
 */

#include <gtest/gtest.h>
#include "redeSocial.h"
#include "grafo.h"

/**
 * @brief Testa CriarPessoa()
 * 
 * Ao passar neste teste, é garantido que CriarPessoa() aloca e inicializa Pessoa corretamente
 */
TEST(CriarPessoaTest, PessoaNormal){
	Pessoa p = CriarPessoa("Pessoa Teste", 50);
	ASSERT_NE((Pessoa)NULL, p);
	EXPECT_EQ(strcmp(p->nome, "Pessoa Teste"), 0);
	EXPECT_EQ(p->rating_provedor,0);
	EXPECT_EQ(p->rating_cliente, 0);
	EXPECT_EQ(p->id, 50);
}

/**
 * @brief Testa CriarProduto()
 * 
 * Ao passar neste teste, é garantido que CriarProduto() aloca e inicializa Produto corretamente
 */
TEST(CriarProdutoTest, ProdutoNormal){
	Produto p = CriarProduto("Carona para Samambaia", "Uma carona para Q5 da Samambaia", SERVICO, 0);
	ASSERT_NE((Produto)NULL, p);
	EXPECT_EQ(strcmp(p->nome, "Carona para Samambaia"), 0);
	EXPECT_EQ(strcmp(p->descricao, "Uma carona para Q5 da Samambaia"), 0);
	EXPECT_EQ(p->tipo, SERVICO);
}

/**
 * @brief Testa CriarTransacao()
 * 
 * Ao passar neste teste, é garantido que CriarTransacao() aloca e inicializa Transacao corretamente
 */
TEST(TransacaoTest, TransacaoNormal){
	Pessoa p = CriarPessoa("Pessoa", 0);
	Produto prod = CriarProduto("Carona para Samambaia", "Uma carona para Q5 da Samambaia", SERVICO, 0);
	Transacao t = CriarTransacao(p, prod, 100);

	ASSERT_EQ(t->cliente, p);
	ASSERT_EQ(t->produto, prod);
	ASSERT_EQ(t->status, PEDIDA);
	ASSERT_EQ(t->provedor, (Pessoa)NULL);
	ASSERT_EQ(t->id, 100);
}

/**
 * @brief Testa CriarRede()
 * 
 * Ao passar neste teste, é garantido que CriarRede() aloca e inicializa Rede corretamente
 */
TEST(CriarRedeTest, RedeNormal){

	Rede r = CriarRede();

	ASSERT_NE((Graph) NULL, r->pessoas);
	ASSERT_EQ((List) NULL, r->transacoes);
}

/**
 * @brief Testa AdicionarPessoa()
 * 
 * Ao passar neste teste, é garantido que AdicionarPessoa() adiciona Pessoa nao repetida na rede
 */
TEST(RedeSocialCRUDTest, AdicionarPessoa){

	Rede r = CriarRede();

	Pessoa p = CriarPessoa("Pessoa", 0);

	ASSERT_TRUE(AdicionarPessoa(r, p));
	EXPECT_FALSE(AdicionarPessoa(r, p)) <<"Pessoa repetida foi adicionada";
}

/**
 * @brief Testa AdicionarProduto()
 * 
 * Ao passar neste teste, é garantido que AdicionarProduto() adiciona Produto nao repetido na rede
 */

TEST(RedeSocialCRUDTest, AdicionarProduto){
	Rede r = CriarRede();

	Produto p = CriarProduto("Carona para Samambaia", "Uma carona para Q5 da Samambaia", SERVICO, 0);

	ASSERT_TRUE(AdicionarProduto(r, p));
	EXPECT_FALSE(AdicionarProduto(r, p));
}

/**
 * @brief Testa AdicionarTransacao()
 * 
 * Ao passar neste teste, é garantido que AdicionarTransacao(): 
 *  - Adiciona Transacao nao repetida na rede
 *  - Nao adiciona Transacao para Produto ou Pessoa inexistente na rede
 */
TEST(RedeSocialCRUDTest, AdicionarTransacao){

	Rede r = CriarRede();

	Pessoa p = CriarPessoa("Pessoa", 0);
	Produto prod = CriarProduto("Carona para Samambaia", "Uma carona para Q5 da Samambaia", SERVICO, 0);
	Transacao t = CriarTransacao(p, prod, 0);

	EXPECT_FALSE(AdicionarTransacao(r, t)); //Produto e Pessoa inexistentes na rede
	AdicionarPessoa(r, p);
	EXPECT_FALSE(AdicionarTransacao(r, t)); //Produto inexistente na rede
	AdicionarProduto(r, prod);
	ASSERT_TRUE(AdicionarTransacao(r, t)); //Transacao Normal
	EXPECT_FALSE(AdicionarTransacao(r, t)); //Transacao repetida

}

/**
 * @brief Testa ExcluirPessoa()
 * 
 * Ao passar neste teste, é garantido que ExcluirPessoa() exclui pessoa de rede
 */

TEST(RedeSocialCRUDTest, ExcluirPessoa){

	Rede r = CriarRede();

	Pessoa p = CriarPessoa("Pessoa", 0);

	AdicionarPessoa(r, p);
	ASSERT_TRUE(ExcluirPessoa(r, p));
	ASSERT_FALSE(ExcluirPessoa(r, p)) <<"Reexclusao";
}
/**
 * @brief Testa ExcluirProduto()
 * 
 * Ao passar neste teste, é garantido que ExcluirProduto() exclui produto de rede
 */
TEST(RedeSocialCRUDTest, ExcluirProduto){
	Rede r = CriarRede();

	Produto p = CriarProduto("Carona para Samambaia", "Uma carona para Q5 da Samambaia", SERVICO, 0);

	AdicionarProduto(r, p);
	ASSERT_TRUE(ExcluirProduto(r, p));
	ASSERT_FALSE(ExcluirProduto(r, p)) <<"Reexclusao";
}
/**
 * @brief Testa ExcluirTransacao()
 * 
 * Ao passar neste teste, é garantido que ExcluirTransacao() exclui transacao de rede
 */
TEST(RedeSocialCRUDTest, ExcluirTransacao){

	Rede r = CriarRede();

	Pessoa p = CriarPessoa("Pessoa", 0);
	Produto prod = CriarProduto("Carona para Samambaia", "Uma carona para Q5 da Samambaia", SERVICO, 0);
	Transacao t = CriarTransacao(p, prod, 0);
	AdicionarPessoa(r, p);
	AdicionarProduto(r, prod);
	AdicionarTransacao(r, t);
	ASSERT_TRUE(ExcluirTransacao(r, t));
	ASSERT_FALSE(ExcluirTransacao(r, t));
}
/**
 * @brief Testa DeletaRede()
 * 
 * Ao passar neste teste, é garantido que DeletaRede() limpa a rede e desaloca da memoria
 */
TEST(RedeSocialCRUDTest, DeletaRede){
	Rede r = CriarRede();

	Pessoa p = CriarPessoa("Pessoa", 0);
	Produto prod = CriarProduto("Carona para Samambaia", "Uma carona para Q5 da Samambaia", SERVICO, 0);
	Transacao t = CriarTransacao(p, prod, 0);
	AdicionarPessoa(r, p);
	AdicionarProduto(r, prod);
	AdicionarTransacao(r, t);

	ASSERT_TRUE(DeletaRede(r));
}
/**
 * @brief Testa AdicionarAmizade()
 * 
 * Ao passar neste teste, é garantido que AdicionarAmizade():
 *  - Adiciona amizade entre duas pessoas
 *  - Nao adiciona amizade repetida
 *  - Nao adiciona amizade para pessoas fora da rede
 */
TEST(RedeSocialConexoesTest, AdicionarAmizade){

	Rede r = CriarRede();

	Pessoa p = CriarPessoa("Pessoa", 0);
	Pessoa p2 = CriarPessoa("Pessoa2", 1);

	EXPECT_FALSE(AdicionarAmizade(r, p, p2));
	AdicionarPessoa(r, p);
	AdicionarPessoa(r, p2);
	EXPECT_TRUE(AdicionarAmizade(r, p, p2));
	EXPECT_TRUE(Amigos(p, p2));
	EXPECT_FALSE(AdicionarAmizade(r, p, p2));

}

/**
 * @brief Testa RemoverAmizade()
 * 
 * Ao passar neste teste, é garantido que RemoverAmizade():
 *  - Nao remove amizade inexistente
 *  - Remove amizade de pessoas presentes na rede
 */
TEST(RedeSocialConexoesTest, RemoverAmizade){
	Rede r = CriarRede();

	Pessoa p = CriarPessoa("Pessoa", 0);
	Pessoa p2 = CriarPessoa("Pessoa2", 1);

	EXPECT_FALSE(RemoverAmizade(r, p, p2));
	
	AdicionarPessoa(r, p);
	AdicionarPessoa(r, p2);
	
	EXPECT_FALSE(RemoverAmizade(r, p, p2));
	
	AdicionarAmizade(r, p, p2);
	
	EXPECT_TRUE(Amigos(p, p2));
	ASSERT_TRUE(RemoverAmizade(r, p, p2));
	EXPECT_FALSE(Amigos(p, p2));

}

/**
 * @brief Testa NotificarTransacao()
 * 
 * Ao passar neste teste, é garantido que NotificarTransacao() notifica quando nao ha filtro
 */
TEST(NotificacoesTest, NotificarTodos){

	Rede r = CriarRede();

	Pessoa p = CriarPessoa("Pessoa", 0); //Cliente
	Pessoa p1 = CriarPessoa("Pessoa1", 1); //Amigo
	Pessoa p2 = CriarPessoa("Pessoa2", 2); //Amigo de Amigo
	Pessoa p3 = CriarPessoa("Pessoa3", 3); //Ja negociou
	Pessoa p4 = CriarPessoa("Pessoa4", 4); //Ja negociou com amigo
	Produto prod = CriarProduto("Carona para Samambaia", "Uma carona para Q5 da Samambaia", SERVICO, 0);

	AdicionarPessoa(r, p);
	AdicionarPessoa(r, p1);
	AdicionarPessoa(r, p2);
	AdicionarPessoa(r, p3);
	AdicionarPessoa(r, p4);
	AdicionarProduto(r, prod);

	AdicionarAmizade(r,p, p1);
	AdicionarAmizade(r,p1, p2);

	int filtros[10] = {0}; // Com todos os filtros falsos ele deve notificar a todos
	
	Transacao t = CriarTransacao(p, prod, 0);
	AdicionarTransacao(r, t);
	NotificarTransacao(r, t, filtros);
	EXPECT_EQ((List)NULL, p->notificacoes);
	EXPECT_EQ(t, (Transacao)(p1->notificacoes->value));
	EXPECT_EQ(t, (Transacao)(p2->notificacoes->value));
	EXPECT_EQ(t, (Transacao)(p3->notificacoes->value));
	EXPECT_EQ(t, (Transacao)(p4->notificacoes->value));

}
/**
 * @brief Testa NotificarTransacao()
 * 
 * Ao passar neste teste, é garantido que NotificarTransacao() notifica quando o filtro é Amigos
 */
TEST(NotificacoesTest, NotificarAmigos){

	Rede r = CriarRede();

	Pessoa p = CriarPessoa("Pessoa", 0); //Cliente
	Pessoa p1 = CriarPessoa("Pessoa1", 1); //Amigo
	Pessoa p2 = CriarPessoa("Pessoa2", 2); //
	Pessoa p3 = CriarPessoa("Pessoa3", 3); //Amigo
	Pessoa p4 = CriarPessoa("Pessoa4", 4); //
	Produto prod = CriarProduto("Carona para Samambaia", "Uma carona para Q5 da Samambaia", SERVICO, 0);

	AdicionarPessoa(r, p);
	AdicionarPessoa(r, p1);
	AdicionarPessoa(r, p2);
	AdicionarPessoa(r, p3);
	AdicionarPessoa(r, p4);
	AdicionarProduto(r, prod);

	AdicionarAmizade(r,p, p1);
	AdicionarAmizade(r,p, p3);

	int filtros[10] = {0};
	filtros[0] = 1; //Seta filtro de amigos
	
	
	Transacao t = CriarTransacao(p, prod, 0);
	AdicionarTransacao(r, t);
	NotificarTransacao(r, t, filtros);

	EXPECT_EQ((List)NULL, p->notificacoes);
	EXPECT_EQ(t, (Transacao)(p1->notificacoes->value));
	EXPECT_EQ((List)NULL, p2->notificacoes);
	EXPECT_EQ(t, (Transacao)(p3->notificacoes->value));
	EXPECT_EQ((List)NULL, p4->notificacoes);

}
/**
 * @brief Testa NotificarTransacao()
 * 
 * Ao passar neste teste, é garantido que NotificarTransacao() notifica quando o filtro é Amigos de Amigos
 */
TEST(NotificacoesTest, NotificarAmigosAmigos){

	Rede r = CriarRede();

	Pessoa p = CriarPessoa("Pessoa", 0); //Cliente
	Pessoa p1 = CriarPessoa("Pessoa1", 1); //Amigo
	Pessoa p2 = CriarPessoa("Pessoa2", 2); //Amigo de Amigo
	Pessoa p3 = CriarPessoa("Pessoa3", 3); //Amigo
	Pessoa p4 = CriarPessoa("Pessoa4", 4); //Amigo de Amigo
	Produto prod = CriarProduto("Carona para Samambaia", "Uma carona para Q5 da Samambaia", SERVICO, 0);

	AdicionarPessoa(r, p);
	AdicionarPessoa(r, p1);
	AdicionarPessoa(r, p2);
	AdicionarPessoa(r, p3);
	AdicionarPessoa(r, p4);
	AdicionarProduto(r, prod);

	AdicionarAmizade(r,p, p1);
	AdicionarAmizade(r,p, p3);

	AdicionarAmizade(r,p1, p2);
	AdicionarAmizade(r,p3, p4);


	int filtros[10] = {0};
	filtros[1] = 1; //Seta filtro
	
	
	Transacao t = CriarTransacao(p, prod, 0);
	AdicionarTransacao(r, t);
	NotificarTransacao(r, t, filtros);

	EXPECT_EQ((List)NULL, p->notificacoes);
	EXPECT_EQ((List)NULL, p1->notificacoes);
	EXPECT_EQ(t, (Transacao)(p2->notificacoes->value));
	EXPECT_EQ((List)NULL, p3->notificacoes);
	EXPECT_EQ(t, (Transacao)(p4->notificacoes->value));

}
/**
 * @brief Testa NotificarTransacao()
 * 
 * Ao passar neste teste, é garantido que NotificarTransacao() notifica quando o filtro é Ja Fez Negocio
 */
TEST(NotificacoesTest, NotificarJaFezNegocios){

	Rede r = CriarRede();

	Pessoa p = CriarPessoa("Pessoa", 0); //Cliente
	Pessoa p1 = CriarPessoa("Pessoa1", 1); 
	Pessoa p2 = CriarPessoa("Pessoa2", 2); //Ja fez negocio
	Pessoa p3 = CriarPessoa("Pessoa3", 3); 
	Pessoa p4 = CriarPessoa("Pessoa4", 4); 
	Produto prod = CriarProduto("Carona para Samambaia", "Uma carona para Q5 da Samambaia", SERVICO, 0);

	AdicionarPessoa(r, p);
	AdicionarPessoa(r, p1);
	AdicionarPessoa(r, p2);
	AdicionarPessoa(r, p3);
	AdicionarPessoa(r, p4);
	AdicionarProduto(r, prod);

	//SIMULA negocio antigo entre p e p2
	adiciona_no(&(p->conhecidos), p2);
	adiciona_no(&(p2->conhecidos), p);

	int filtros[10] = {0};
	filtros[2] = 1; //Seta filtro
	
	
	Transacao t = CriarTransacao(p, prod, 0);
	AdicionarTransacao(r, t);
	NotificarTransacao(r, t, filtros);

	EXPECT_EQ((List)NULL, p->notificacoes);
	EXPECT_EQ((List)NULL, p1->notificacoes);
	EXPECT_EQ(t, (Transacao)(p2->notificacoes->value));
	EXPECT_EQ((List)NULL, p3->notificacoes);
	EXPECT_EQ((List)NULL, p4->notificacoes);

}
/**
 * @brief Testa NotificarTransacao()
 * 
 * Ao passar neste teste, é garantido que NotificarTransacao() notifica quando o filtro é Ja Fez Negocio com Amigos
 */
TEST(NotificacoesTest, NotificarJaFezNegociosComAmigos){

	Rede r = CriarRede();

	Pessoa p = CriarPessoa("Pessoa", 0); //Cliente
	Pessoa p1 = CriarPessoa("Pessoa1", 1); //Amigo
	Pessoa p2 = CriarPessoa("Pessoa2", 2); //Ja fez negocio com amigo
	Pessoa p3 = CriarPessoa("Pessoa3", 3); //Amigo
	Pessoa p4 = CriarPessoa("Pessoa4", 4); // Ja fez negocio com amigo e com cliente
	Produto prod = CriarProduto("Carona para Samambaia", "Uma carona para Q5 da Samambaia", SERVICO, 0);

	AdicionarPessoa(r, p);
	AdicionarPessoa(r, p1);
	AdicionarPessoa(r, p2);
	AdicionarPessoa(r, p3);
	AdicionarPessoa(r, p4);
	AdicionarProduto(r, prod);

	//SIMULA negocio antigo entre p e p4
	adiciona_no(&(p->conhecidos), p4);
	adiciona_no(&(p4->conhecidos), p);

	//SIMULA negocio antigo entre p1 e p4
	adiciona_no(&(p1->conhecidos), p4);
	adiciona_no(&(p4->conhecidos), p1);

	//SIMULA negocio antigo entre p3 e p2
	adiciona_no(&(p3->conhecidos), p2);
	adiciona_no(&(p2->conhecidos), p3);

	AdicionarAmizade(r,p, p1);
	AdicionarAmizade(r,p, p3);

	int filtros[10] = {0};
	filtros[3] = 1; //Seta filtro de negocios com amigos
	
	
	Transacao t = CriarTransacao(p, prod, 0);
	AdicionarTransacao(r, t);
	NotificarTransacao(r, t, filtros);

	EXPECT_EQ((List)NULL, p->notificacoes);
	EXPECT_EQ((List)NULL, p1->notificacoes);
	EXPECT_EQ(t, (Transacao)(p2->notificacoes->value));
	EXPECT_EQ((List)NULL, p3->notificacoes);
	EXPECT_EQ(t, (Transacao)(p4->notificacoes->value));

}

/**
 * @brief Testa NotificarTransacao()
 * 
 * Ao passar neste teste, é garantido que NotificarTransacao() notifica quando o filtro é Acostumado
 */
TEST(NotificacoesTest, NotificarAcostumado){

	Rede r = CriarRede();

	Pessoa p = CriarPessoa("Pessoa", 0); //Cliente
	Pessoa p1 = CriarPessoa("Pessoa1", 1); 
	Pessoa p2 = CriarPessoa("Pessoa2", 2); //Ja fez transacao desse produto antes
	Pessoa p3 = CriarPessoa("Pessoa3", 3); 
	Pessoa p4 = CriarPessoa("Pessoa4", 4); 
	Produto prod = CriarProduto("Carona para Samambaia", "Uma carona para Q5 da Samambaia", SERVICO, 0);

	AdicionarPessoa(r, p);
	AdicionarPessoa(r, p1);
	AdicionarPessoa(r, p2);
	AdicionarPessoa(r, p3);
	AdicionarPessoa(r, p4);
	AdicionarProduto(r, prod);

	//SIMULA transacao concluida
	Transacao t_2 = CriarTransacao(p4, prod, 213);
	AdicionarTransacao(r, t_2);
	t_2->provedor = p2;
	adiciona_no(&(p2->transacoes), t_2);

	int filtros[10] = {0};
	filtros[4] = 1; //Seta filtro
	
	
	Transacao t = CriarTransacao(p, prod, 0);
	AdicionarTransacao(r, t);
	NotificarTransacao(r, t, filtros);

	EXPECT_EQ((List)NULL, p->notificacoes);
	EXPECT_EQ((List)NULL, p1->notificacoes);
	EXPECT_EQ(t, (Transacao)(p2->notificacoes->value));
	EXPECT_EQ((List)NULL, p3->notificacoes);
	EXPECT_EQ((List)NULL, p4->notificacoes);

}
/**
 * @brief Testa AceitarTransacao()
 * 
 * Ao passar neste teste, é garantido que AceitaTransacao() envia uma oferta ao cliente e remove transacao das notificacoes
 */
TEST(NegociosTest, AceitarTransacao){

	Rede r = CriarRede();

	Pessoa p = CriarPessoa("Pessoa", 0); //Cliente
	Pessoa p1 = CriarPessoa("Pessoa1", 1); 
	Produto prod = CriarProduto("Carona para Samambaia", "Uma carona para Q5 da Samambaia", SERVICO, 0);

	AdicionarPessoa(r, p);
	AdicionarPessoa(r, p1);
	AdicionarProduto(r, prod);
	Transacao t = CriarTransacao(p, prod, 0);
	AdicionarTransacao(r, t);
	NotificarTransacao(r, t, NULL);

	AceitarTransacao(r, t, p1);
	EXPECT_EQ(p1, (Pessoa)t->ofertas->value);
	EXPECT_EQ(p1->notificacoes, (List)NULL);

}
/**
 * @brief Testa AceitarOferta()
 * 
 * Ao passar neste teste, é garantido que AceitarOferta() seta o usuario que provera o servico descrito na transacao
 */
TEST(NegociosTest, AceitarOferta){

	Rede r = CriarRede();

	Pessoa p = CriarPessoa("Pessoa", 0); //Cliente
	Pessoa p1 = CriarPessoa("Pessoa1", 1); 
	Produto prod = CriarProduto("Carona para Samambaia", "Uma carona para Q5 da Samambaia", SERVICO, 0);

	AdicionarPessoa(r, p);
	AdicionarPessoa(r, p1);
	AdicionarProduto(r, prod);
	Transacao t = CriarTransacao(p, prod, 0);
	AdicionarTransacao(r, t);
	NotificarTransacao(r, t, NULL);

	AceitarTransacao(r, t, p1);
	AceitarOferta(r, t, p1);

	ASSERT_EQ(t->provedor, p1);
	ASSERT_EQ((Transacao)p1->transacoes->value, t);


}
/**
 * @brief Testa ConcluirTransacao()
 * 
 * Ao passar neste teste, é garantido que ConcluirTransacao() transforma a transacao em Pendente e Adiciona usuarios como 
 * conhecidos(Ja fizeram negocios)
 */
TEST(NegociosTest, ConcluirTransacao){

	Rede r = CriarRede();

	Pessoa p = CriarPessoa("Pessoa", 0); //Cliente
	Pessoa p1 = CriarPessoa("Pessoa1", 1); 
	Produto prod = CriarProduto("Carona para Samambaia", "Uma carona para Q5 da Samambaia", SERVICO, 0);

	AdicionarPessoa(r, p);
	AdicionarPessoa(r, p1);
	AdicionarProduto(r, prod);
	Transacao t = CriarTransacao(p, prod, 0);
	AdicionarTransacao(r, t);
	NotificarTransacao(r, t, NULL);

	AceitarTransacao(r, t, p1);
	AceitarOferta(r, t, p1);//AceitarOferta chama ConcluirTransacao

	ASSERT_TRUE(Conhecidos(p, p1));
	ASSERT_EQ(t->status, PENDENTE);


}
/**
 * @brief Testa AvaliarTransacao()
 * 
 * Ao passar neste teste, é garantido que AvaliarTransacao() modifica o Karma dos usuarios e adiciona comentarios sobre ele
 */
TEST(NegociosTest, AvaliarTransacao){

	Rede r = CriarRede();

	Pessoa p = CriarPessoa("Pessoa", 0); //Cliente
	Pessoa p1 = CriarPessoa("Pessoa1", 1); 
	Produto prod = CriarProduto("Carona para Samambaia", "Uma carona para Q5 da Samambaia", SERVICO, 0);

	AdicionarPessoa(r, p);
	AdicionarPessoa(r, p1);
	AdicionarProduto(r, prod);
	Transacao t = CriarTransacao(p, prod, 0);
	AdicionarTransacao(r, t);
	NotificarTransacao(r, t, NULL);

	AceitarTransacao(r, t, p1);
	AceitarOferta(r, t, p1);

	AvaliarTransacao(r, t, p, "Gostei Muito", 4);
	AvaliarTransacao(r, t, p1, "Muito rude", -2);


	ASSERT_EQ(4, p1->rating_provedor);
	ASSERT_EQ(-2, p->rating_cliente);	
	
	ASSERT_EQ(0,strcmp("Gostei Muito", (char*)(p1->comentarios->value)));
	ASSERT_EQ(0,strcmp("Muito rude", (char*)(p->comentarios->value)));

	ASSERT_EQ(t->status, CONCLUIDA);

}
/**
 * @brief Testa FiltrarTransacao()
 * 
 * Ao passar neste teste, é garantido que FiltrarTransacao() retorna apenas as Transacoes aceitas pelo fitro
 */
TEST(RedeSocialTest, FiltrarTransacao){

	Rede r = CriarRede();

	Pessoa p = CriarPessoa("Pessoa", 0); //Cliente
	Pessoa p1 = CriarPessoa("Pessoa1", 1); 
	Produto prod = CriarProduto("Carona para Samambaia", "Uma carona para Q5 da Samambaia", SERVICO, 0);
	Transacao t1 = CriarTransacao(p, prod, 1);
	Transacao t2 = CriarTransacao(p, prod, 2);
	Transacao t3 = CriarTransacao(p, prod, 3);
	Transacao t4 = CriarTransacao(p, prod, 4);

	t1->status = PENDENTE;
	t2->status = PENDENTE;
	t3->status = PENDENTE;
	t4->status = CONCLUIDA;

	List lista = cria_lista();

	adiciona_no(&lista, t1);
	adiciona_no(&lista, t2);
	adiciona_no(&lista, t3);
	adiciona_no(&lista, t4);
	
	List lista2 = FiltrarTransacao(lista, PENDENTE);

	ASSERT_EQ(tamanho_list(lista), 4);
	ASSERT_EQ(tamanho_list(lista2), 3);

}

/**
 * @brief Testa ProdutoByID()
 * 
 * Ao passar neste teste, é garantido que ProdutoByID() retorna o produto correto
 */
TEST(RedeSocialTest, ProdutoByID){
	Rede r = CriarRede();

	Produto p = CriarProduto("Carona para Samambaia", "Uma carona para Q5 da Samambaia", SERVICO, 0);

	AdicionarProduto(r, p);

	ASSERT_EQ(ProdutoByID(r, p->id), p);

}
/**
 * @brief Testa TransacaoByID()
 * 
 * Ao passar neste teste, é garantido que TransacaoByID() retorna a transacao correta
 */
TEST(RedeSocialTest, TransacaoByID){
	Rede r = CriarRede();

	Pessoa p = CriarPessoa("Pessoa", 0);
	Produto prod = CriarProduto("Carona para Samambaia", "Uma carona para Q5 da Samambaia", SERVICO, 0);
	Transacao t = CriarTransacao(p, prod, 0);

	AdicionarPessoa(r, p);
	AdicionarProduto(r, prod);
	AdicionarTransacao(r, t);
	ASSERT_EQ(TransacaoByID(r, t->id), t);
}
/**
 * @brief Testa PessoaByID()
 * 
 * Ao passar neste teste, é garantido que PessoaByID() retorna a pessoa correta
 */
TEST(RedeSocialTest, PessoaByID){

	Rede r = CriarRede();

	Pessoa p = CriarPessoa("Pessoa", 0);

	AdicionarPessoa(r, p);

	ASSERT_EQ(PessoaByID(r, p->id), p);
}
/**
 * @brief Testa RedeFile()
 * 
 * Ao passar neste teste, é garantido que RedeFile() le corretamente do arquivo gerado por salva rede utilizando todas
 * as funcoes complementares
 */
TEST(PersistenciaTest, RedeFileESalvaRede){

	Rede r = CriarRede();

	Pessoa p = CriarPessoa("Pessoa", 0); 
	Pessoa p1 = CriarPessoa("Pessoa1", 1); 
	Pessoa p2 = CriarPessoa("Pessoa2", 2); 
	Pessoa p3 = CriarPessoa("Pessoa3", 3); 
	Pessoa p4 = CriarPessoa("Pessoa4", 4); 
	Produto prod1 = CriarProduto("Carona para Samambaia", "Uma carona para Q5 da Samambaia", SERVICO, 0);
	Produto prod2 = CriarProduto("Manga", "Uma manga madura", PRODUTO, 23);
	Produto prod3 = CriarProduto("Abraco", "Um Abraco para pessoas tristes", SERVICO, 48);
	Produto prod4 = CriarProduto("Computador Usado", "Um computador de 1994", PRODUTO, 1010);

	Transacao t1 = CriarTransacao(p4, prod2, 50);
	Transacao t2 = CriarTransacao(p1, prod3, 9);

	AdicionarPessoa(r, p);
	AdicionarPessoa(r, p1);
	AdicionarPessoa(r, p2);
	AdicionarPessoa(r, p3);
	AdicionarPessoa(r, p4);

	AdicionarAmizade(r, p, p4);
	AdicionarAmizade(r, p1, p4);
	AdicionarAmizade(r, p3, p2);

	AdicionarProduto(r, prod1);
	AdicionarProduto(r, prod2);
	AdicionarProduto(r, prod3);
	AdicionarProduto(r, prod4);

	AdicionarTransacao(r, t1);
	AdicionarTransacao(r, t2);

	SalvaRede(r, "TestPersist");
	Rede r2 = RedeFile("TestPersist");

	ASSERT_NE((Pessoa)NULL, PessoaByID(r2, p->id));
	ASSERT_NE((Pessoa)NULL, PessoaByID(r2, p1->id));
	ASSERT_NE((Pessoa)NULL, PessoaByID(r2, p2->id));
	ASSERT_NE((Pessoa)NULL, PessoaByID(r2, p3->id));
	ASSERT_NE((Pessoa)NULL, PessoaByID(r2, p4->id));

	ASSERT_NE((Produto)NULL, ProdutoByID(r2, prod1->id));
	ASSERT_NE((Produto)NULL, ProdutoByID(r2, prod2->id));
	ASSERT_NE((Produto)NULL, ProdutoByID(r2, prod3->id));
	ASSERT_NE((Produto)NULL, ProdutoByID(r2, prod4->id));

	ASSERT_NE((Transacao)NULL, TransacaoByID(r2, t2->id));
	ASSERT_NE((Transacao)NULL, TransacaoByID(r2, t1->id));


	ASSERT_TRUE(Amigos(PessoaByID(r2, p->id), PessoaByID(r2, p4->id)));
	ASSERT_TRUE(Amigos(PessoaByID(r2, p1->id), PessoaByID(r2, p4->id)));
	ASSERT_TRUE(Amigos(PessoaByID(r2, p3->id), PessoaByID(r2, p2->id)));

}
int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}